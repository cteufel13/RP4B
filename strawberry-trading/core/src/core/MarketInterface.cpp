#include <core/MarketInterface.hpp>
#include <nlohmann/json.hpp>
#include <logger_alias.hpp>
#include <string>
#include <iostream>

MarketInterface::MarketInterface() : trading_client(), option_client(), market_client() {};

bool MarketInterface::order(std::string symbol,
                            float qty,
                            std::optional<float> notional,
                            OrderSide side,
                            OrderType type,
                            TimeInForce time_in_force,
                            OrderClass orderclass,
                            bool extended_hours)
{

    Order order = Order(symbol,
                        qty,
                        notional,
                        side,
                        type,
                        time_in_force,
                        orderclass,
                        extended_hours);

    std::string response = trading_client.submit_order(order);
    nlohmann::json response_json = nlohmann::json::parse(response);

    if (response_json["filled_at"].is_null())
    {
        logger.warning("[MarketInterface::order] Order was not filled. May be after hours.");
        return false;
    }
    else
    {
        logger.info("[MarketInterface::order] Order was filled successfully at " + response_json["filled_at"].get<std::string>() + ".");
        return true;
    };
};

std::vector<Position> MarketInterface::getAllPositions()
{
    std::string response = trading_client.get_all_positions();
    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.size() == 0)
    {
        logger.warning("[MarketInterface::getAllPositions] Positions is empty");
        return std::vector<Position>();
    }
    else
    {
        std::vector<Position> positions;
        for (const auto &pos : response_json)
        {
            positions.push_back(parsePosition(pos));
        }
        logger.info("[MarketInterface::getAllPositions] Retrieved Positions");
        return positions;
    }
};

Position MarketInterface::getOpenPosition(const std::string &symbol_or_asset_id)
{
    std::string response = trading_client.get_open_position(symbol_or_asset_id);
    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::getOpenPosition] Position could not be found.");
        return Position{};
    }
    else
    {
        Position position = parsePosition(response_json);
        logger.info("[MarketInterface::getOpenPosition] Retrieved position of " + symbol_or_asset_id + ".");
        return position;
    };
};

void MarketInterface::closeAllPositions()
{
    std::string response = trading_client.close_all_positions();
    logger.info("[MarketInterface::getOpenPosition] Closed all positions.");
};

void MarketInterface::closePosition(const std::string &symbol_or_asset_id)
{
    std::string response = trading_client.close_position(symbol_or_asset_id);
    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::closePosition] Position could not be found.");
    }
    else
    {
        logger.info("[MarketInterface::closePosition] Closed Position of " + symbol_or_asset_id + ".");
    };
};

TimeSeries MarketInterface::getPortfolioHistory()
{
    std::string response = trading_client.get_portfolio_history();
    nlohmann::json response_json = nlohmann::json::parse(response);
    if (response_json.contains("code"))
    {
        logger.error("[MarketInterface::getPortfolioHistory] History could not be found.");
        return TimeSeries{};
    }

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
    nlohmann::json response_json = nlohmann::json::parse(response);

    if (!response_json.contains("option_contracts"))
    {
        logger.error("[MarketInterface::getOptionContracts] Error with Contract Retrieval");
        return std::vector<Option>{};
    }
    response_json = response_json["option_contracts"];

    std::vector<Option> options;

    for (const auto &opt : response_json)
    {
        options.push_back(parseOption(opt));
    };
    return options;
};

Option MarketInterface::getOptionContract(const std::string &symbol_asset_id)
{
    std::string response = trading_client.get_option_contract(symbol_asset_id);
    std::cout << response << std::endl;
    nlohmann::json response_json = nlohmann::json::parse(response);

    return parseOption(response_json);
}