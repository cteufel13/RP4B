#include <core/MarketInterface.hpp>
#include <nlohmann/json.hpp>
#include <logger_alias.hpp>
#include <string>
#include <iostream>

MarketInterface::MarketInterface() : trading_client(), option_client(), market_client()
{
    logger.info("[MarketInterface] Constructor - Initialized trading, option, and market clients");
};

bool MarketInterface::order(std::string symbol,
                            float qty,
                            std::optional<float> notional,
                            OrderSide side,
                            OrderType type,
                            TimeInForce time_in_force,
                            OrderClass orderclass,
                            bool extended_hours)
{
    logger.debug("[MarketInterface::order] Starting order for symbol: " + symbol + ", qty: " + std::to_string(qty));

    Order order = Order(symbol,
                        qty,
                        notional,
                        side,
                        type,
                        time_in_force,
                        orderclass,
                        extended_hours);

    logger.debug("[MarketInterface::order] Order object created, submitting to trading client");
    std::string response = trading_client.submit_order(order);
    logger.debug("[MarketInterface::order] Received response from trading client");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (!response_json.contains("filled_at"))
    {
        logger.warning("[MarketInterface::order] Order was not filled. May be after hours.");
        return false;
    }
    else
    {
        logger.info("[MarketInterface::order] Order was filled successfully.");
        return true;
    };
};

std::vector<Position> MarketInterface::getAllPositions()
{
    logger.debug("[MarketInterface::getAllPositions] Requesting all positions from trading client");
    std::string response = trading_client.get_all_positions();
    logger.debug("[MarketInterface::getAllPositions] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.size() == 0)
    {
        logger.warning("[MarketInterface::getAllPositions] Positions is empty");
        return std::vector<Position>();
    }
    else
    {
        logger.debug("[MarketInterface::getAllPositions] Found " + std::to_string(response_json.size()) + " positions, parsing...");
        std::vector<Position> positions;
        for (const auto &pos : response_json)
        {
            positions.push_back(parsePosition(pos));
        }
        logger.info("[MarketInterface::getAllPositions] Retrieved " + std::to_string(positions.size()) + " positions successfully");
        return positions;
    }
};

Position MarketInterface::getOpenPosition(const std::string &symbol_or_asset_id)
{
    logger.debug("[MarketInterface::getOpenPosition] Requesting position for: " + symbol_or_asset_id);
    std::string response = trading_client.get_open_position(symbol_or_asset_id);
    logger.debug("[MarketInterface::getOpenPosition] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::getOpenPosition] Position could not be found for " + symbol_or_asset_id);
        return Position{};
    }
    else
    {
        Position position = parsePosition(response_json);
        logger.info("[MarketInterface::getOpenPosition] Retrieved position of " + symbol_or_asset_id + " successfully");
        return position;
    };
};

void MarketInterface::closeAllPositions()
{
    logger.debug("[MarketInterface::closeAllPositions] Requesting to close all positions");
    std::string response = trading_client.close_all_positions();
    logger.info("[MarketInterface::closeAllPositions] Closed all positions successfully");
};

void MarketInterface::closePosition(const std::string &symbol_or_asset_id)
{
    logger.debug("[MarketInterface::closePosition] Requesting to close position for: " + symbol_or_asset_id);
    std::string response = trading_client.close_position(symbol_or_asset_id);
    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::closePosition] Position could not be found for " + symbol_or_asset_id);
    }
    else
    {
        logger.info("[MarketInterface::closePosition] Closed position of " + symbol_or_asset_id + " successfully");
    };
};

TimeSeries MarketInterface::getPortfolioHistory()
{
    logger.debug("[MarketInterface::getPortfolioHistory] Requesting portfolio history");
    std::string response = trading_client.get_portfolio_history();
    logger.debug("[MarketInterface::getPortfolioHistory] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::getPortfolioHistory] History could not be found");
        return TimeSeries{};
    }

    logger.debug("[MarketInterface::getPortfolioHistory] Parsing portfolio history data");
    TimeSeries series;

    std::vector<int64_t> timestamps = response_json["timestamp"];
    std::vector<double> equity = response_json["equity"];
    std::vector<double> profit_loss = response_json["profit_loss"];
    std::vector<double> profit_loss_pct = response_json["profit_loss_pct"];

    for (size_t i = 0; i < timestamps.size(); ++i)
    {
        TimeSeriesPoint point;
        point.timestamp = from_unix_timestamp(timestamps[i]);
        point.values["equity"] = equity[i];
        point.values["profit_loss"] = profit_loss[i];
        point.values["profit_loss_pct"] = profit_loss_pct[i];
        series.addPoint(point);
    }
    logger.info("[MarketInterface::getPortfolioHistory] Successfully parsed " + std::to_string(timestamps.size()) + " portfolio history points");
    return series;
};

std::optional<std::string> convertToString(const std::optional<Date> &optDate)
{
    if (optDate.has_value())
    {
        return optDate->to_string(); // use -> to access Date inside optional
    }
    return std::nullopt;
}

std::vector<Option> MarketInterface::getOptionContracts(std::vector<std::string> underlying_symbols,
                                                        AssetStatus status,
                                                        Date expiration_date,
                                                        std::optional<Date> expiration_date_gte,
                                                        std::optional<Date> expiration_date_lte,
                                                        std::optional<std::string> root_symbol,
                                                        ContractType type,
                                                        ExerciseStyle style,
                                                        std::optional<std::string> strike_price_gte,
                                                        std::optional<std::string> strike_price_lte,
                                                        std::optional<int> limit)
{
    logger.debug("[MarketInterface::getOptionContracts] Requesting option contracts for " + std::to_string(underlying_symbols.size()) + " symbols");
    GetOptionContractsRequest req = GetOptionContractsRequest(underlying_symbols,
                                                              status,
                                                              convertToString(expiration_date),
                                                              convertToString(expiration_date_gte),
                                                              convertToString(expiration_date_lte),
                                                              root_symbol,
                                                              type,
                                                              style,
                                                              strike_price_gte,
                                                              strike_price_lte,
                                                              limit);
    std::string response = trading_client.get_option_contracts(req);
    logger.debug("[MarketInterface::getOptionContracts] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);

    if (!response_json.contains("option_contracts"))
    {
        logger.error("[MarketInterface::getOptionContracts] Error with contract retrieval - no option_contracts field in response");
        return std::vector<Option>{};
    }
    response_json = response_json["option_contracts"];

    logger.debug("[MarketInterface::getOptionContracts] Found " + std::to_string(response_json.size()) + " option contracts, parsing...");
    std::vector<Option> options;

    for (const auto &opt : response_json)
    {
        options.push_back(parseOption(opt));
    };
    logger.info("[MarketInterface::getOptionContracts] Successfully retrieved " + std::to_string(options.size()) + " option contracts");
    return options;
};

Option MarketInterface::getOptionContract(const std::string &symbol_asset_id)
{
    logger.debug("[MarketInterface::getOptionContract] Requesting option contract for: " + symbol_asset_id);
    std::string response = trading_client.get_option_contract(symbol_asset_id);
    logger.debug("[MarketInterface::getOptionContract] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);

    Option option = parseOption(response_json);
    logger.info("[MarketInterface::getOptionContract] Successfully retrieved option contract for " + symbol_asset_id);
    return option;
}

std::vector<TimeSeries> MarketInterface::requestStockBars(std::vector<std::string> symbols,
                                                          TimeFrame tframe,
                                                          Date start,
                                                          std::optional<Date> end,
                                                          int limit)
{
    logger.debug("[MarketInterface::requestStockBars] Requesting stock bars for " + std::to_string(symbols.size()) + " symbols");

    StockBarsRequest req = StockBarsRequest(symbols, tframe, start.to_string(), convertToString(end), limit);
    std::string response = market_client.get_stock_bars(req);
    logger.debug("[MarketInterface::requestStockBars] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (!response_json.contains("bars"))
    {
        logger.error("[MarketInterface::requestStockBars] Error with bars retrieval - no bars field in response");
        return std::vector<TimeSeries>{};
    }
    else
    {
        response_json = response_json["bars"];
        logger.debug("[MarketInterface::requestStockBars] Processing bars data for stocks");
        std::vector<TimeSeries> output;

        for (const auto &stock : response_json)
        {
            TimeSeries ts;

            for (const auto &timepoint : stock)
            {
                TimeSeriesPoint entry;
                entry.timestamp = from_tz_string(timepoint["t"]);
                entry.values["open"] = timepoint["o"];
                entry.values["high"] = timepoint["h"];
                entry.values["low"] = timepoint["l"];
                entry.values["close"] = timepoint["c"];
                entry.values["volume"] = timepoint["v"];
                entry.values["vwap"] = timepoint["vw"];

                ts.addPoint(entry);
            };

            output.push_back(ts);
        };

        logger.info("[MarketInterface::requestStockBars] Successfully retrieved stock bars for " + std::to_string(output.size()) + " symbols");
        return output;
    }
};

std::vector<TimeSeriesPoint> MarketInterface::requestStockBarsLatest(const std::vector<std::string> &symbols)
{
    logger.debug("[MarketInterface::requestStockBarsLatest] Requesting latest stock bars for " + std::to_string(symbols.size()) + " symbols");
    StockLatestBarRequest req = StockLatestBarRequest(symbols);
    std::string response = market_client.get_stock_latest_bars(req);
    logger.debug("[MarketInterface::requestStockBarsLatest] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (!response_json.contains("bars"))
    {
        logger.error("[MarketInterface::requestStockBarsLatest] Error with bars retrieval - no bars field in response");
        return std::vector<TimeSeriesPoint>{};
    };
    response_json = response_json["bars"];

    logger.debug("[MarketInterface::requestStockBarsLatest] Processing latest bars data");
    std::vector<TimeSeriesPoint> output;

    for (const auto &stock : response_json)
    {
        TimeSeriesPoint entry;
        entry.timestamp = from_tz_string(stock["t"]);
        entry.values["open"] = stock["o"];
        entry.values["high"] = stock["h"];
        entry.values["low"] = stock["l"];
        entry.values["close"] = stock["c"];
        entry.values["volume"] = stock["v"];
        entry.values["vwap"] = stock["vw"];
        output.push_back(entry);
    };
    logger.info("[MarketInterface::requestStockBarsLatest] Successfully retrieved latest bars for " + std::to_string(output.size()) + " symbols");
    return output;
};

std::vector<TimeSeries> MarketInterface::requestOptionBars(std::vector<std::string> symbols,
                                                           TimeFrame tframe,
                                                           std::optional<std::string> start,
                                                           std::optional<std::string> end,
                                                           std::optional<int> limit)
{
    logger.debug("[MarketInterface::requestOptionBars] Requesting option bars for " + std::to_string(symbols.size()) + " symbols");
    OptionBarRequest req = OptionBarRequest(symbols,
                                            tframe,
                                            start,
                                            end,
                                            limit);

    std::string response = option_client.get_option_bars(req);
    logger.debug("[MarketInterface::requestOptionBars] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (!response_json.contains("bars"))
    {
        logger.error("[MarketInterface::requestOptionBars] Error with bars retrieval - no bars field in response");
        return std::vector<TimeSeries>{};
    }
    else
    {
        response_json = response_json["bars"];
        logger.debug("[MarketInterface::requestOptionBars] Processing option bars data");
        std::vector<TimeSeries> output;

        for (const auto &option : response_json)
        {
            TimeSeries ts;

            for (const auto &timepoint : option)
            {
                TimeSeriesPoint entry;
                entry.timestamp = from_tz_string(timepoint["t"]);
                entry.values["open"] = timepoint["o"];
                entry.values["high"] = timepoint["h"];
                entry.values["low"] = timepoint["l"];
                entry.values["close"] = timepoint["c"];
                entry.values["volume"] = timepoint["v"];
                entry.values["vwap"] = timepoint["vw"];
                entry.values["n"] = timepoint["n"];

                ts.addPoint(entry);
            };

            output.push_back(ts);
        };

        logger.info("[MarketInterface::requestOptionBars] Successfully retrieved option bars for " + std::to_string(output.size()) + " symbols");
        return output;
    };
};

std::vector<TimeSeriesPoint> MarketInterface::requestOptionBarsLatest(const std::vector<std::string> &options)
{
    logger.debug("[MarketInterface::requestOptionBarsLatest] Requesting latest option bars for " + std::to_string(options.size()) + " options");
    OptionLatestBarRequest req = OptionLatestBarRequest(options);
    std::string response = option_client.get_option_latest_bars(req);
    logger.debug("[MarketInterface::requestOptionBarsLatest] Received response, parsing JSON");

    nlohmann::json response_json = nlohmann::json::parse(response);
    if (!response_json.contains("bars"))
    {
        logger.error("[MarketInterface::requestOptionBarsLatest] Error with bars retrieval - no bars field in response");
        return std::vector<TimeSeriesPoint>{};
    };
    response_json = response_json["bars"];

    logger.debug("[MarketInterface::requestOptionBarsLatest] Processing latest option bars data");
    std::vector<TimeSeriesPoint> output;

    for (const auto &option : response_json)
    {
        TimeSeriesPoint entry;
        entry.timestamp = from_tz_string(option["t"]);
        entry.values["open"] = option["o"];
        entry.values["high"] = option["h"];
        entry.values["low"] = option["l"];
        entry.values["close"] = option["c"];
        entry.values["volume"] = option["v"];
        entry.values["vwap"] = option["vw"];
        output.push_back(entry);
    };
    logger.info("[MarketInterface::requestOptionBarsLatest] Successfully retrieved latest option bars for " + std::to_string(output.size()) + " options");
    return output;
};

OptionChain MarketInterface::requestOptionChains(
    std::string underlying_symbol,
    std::optional<ContractType> type,
    std::optional<double> strike_price_gte,
    std::optional<double> strike_price_lte,
    std::optional<std::string> expiration_date,
    std::optional<std::string> expiration_date_gte,
    std::optional<std::string> expiration_date_lte,
    std::optional<std::string> root_symbol,
    std::optional<std::chrono::system_clock::time_point> updated_since,
    std::string feed,
    int limit)
{
    logger.debug("[MarketInterface::requestOptionChains] Requesting option chain for: " + underlying_symbol);

    OptionChainRequest req(
        std::move(underlying_symbol),
        std::move(feed),
        limit,
        type,
        strike_price_gte,
        strike_price_lte,
        std::move(expiration_date),
        std::move(expiration_date_gte),
        std::move(expiration_date_lte),
        std::move(root_symbol),
        updated_since);

    std::string response = option_client.get_options_chains(req);
    logger.debug("[MarketInterface::requestOptionChains] Received response, creating OptionChain object");
    OptionChain output(response);
    logger.info("[MarketInterface::requestOptionChains] Successfully retrieved option chain");

    return output;
}

std::vector<float> MarketInterface::getDeltas(OptionChain &optchain)
{
    logger.debug("[MarketInterface::getDeltas] Extracting deltas from option chain");
    std::vector<float> deltas = optchain.get_deltas();
    logger.info("[MarketInterface::getDeltas] Successfully extracted " + std::to_string(deltas.size()) + " delta values");
    return deltas;
};

std::vector<float> MarketInterface::getGammas(OptionChain &optchain)
{
    logger.debug("[MarketInterface::getGammas] Extracting gammas from option chain");
    std::vector<float> gammas = optchain.get_gammas();
    logger.info("[MarketInterface::getGammas] Successfully extracted " + std::to_string(gammas.size()) + " gamma values");
    return gammas;
};

std::vector<float> MarketInterface::getVegas(OptionChain &optchain)
{
    logger.debug("[MarketInterface::getVegas] Extracting vegas from option chain");
    std::vector<float> vegas = optchain.get_vegas();
    logger.info("[MarketInterface::getVegas] Successfully extracted " + std::to_string(vegas.size()) + " vega values");
    return vegas;
};

std::vector<float> MarketInterface::getRhos(OptionChain &optchain)
{
    logger.debug("[MarketInterface::getRhos] Extracting rhos from option chain");
    std::vector<float> rhos = optchain.get_rhos();
    logger.info("[MarketInterface::getRhos] Successfully extracted " + std::to_string(rhos.size()) + " rho values");
    return rhos;
};

std::vector<float> MarketInterface::getThetas(OptionChain &optchain)
{
    logger.debug("[MarketInterface::getThetas] Extracting thetas from option chain");
    std::vector<float> thetas = optchain.get_thetas();
    logger.info("[MarketInterface::getThetas] Successfully extracted " + std::to_string(thetas.size()) + " theta values");
    return thetas;
};