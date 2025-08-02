#include <api/market_data_client.hpp>
#include <api/option_data_client.hpp>
#include <api/trading_client.hpp>
#include <common/optionchain.hpp>
#include <common/option.hpp>
#include <common/position.hpp>
#include <common/timeseries.hpp>
#include <utils/json.hpp>
#include <utils/position_utils.hpp>
#include <utils/timeseries_utils.hpp>
#include <utils/option_utils.hpp>

#include <string>

class MarketInterface
{
public:
    MarketInterface();
    // Trading:
    bool order(std::string symbol,
               float qty = 1.0,
               std::optional<float> notional = std::nullopt,
               OrderSide side = OrderSide::BUY,
               OrderType type = OrderType::MARKET,
               TimeInForce time_in_force = TimeInForce::DAY,
               OrderClass orderclass = OrderClass::SIMPLE,
               bool extended_hours = false); // handles interaction with Order Class
    std::vector<Position> getAllPositions();
    Position getOpenPosition(const std::string &symbol_or_asset_id);
    void closeAllPositions();
    void closePosition(const std::string &symbol_or_asset_id);
    TimeSeries getPortfolioHistory();
    std::vector<Option> getOptionContracts(std::vector<std::string> underlying_symbols,
                                           AssetStatus status = AssetStatus::ACTIVE,
                                           Date expiration_date = (Date::now() + std::chrono::days{5}),
                                           std::optional<Date> expiration_date_gte = std::nullopt,
                                           std::optional<Date> expiration_date_lte = std::nullopt,
                                           std::optional<std::string> root_symbol = std::nullopt,
                                           ContractType type = ContractType::CALL,
                                           ExerciseStyle style = ExerciseStyle::AMERICAN,
                                           std::optional<std::string> strike_price_gte = std::nullopt,
                                           std::optional<std::string> strike_price_lte = std::nullopt,
                                           std::optional<int> limit = std::nullopt);
    Option getOptionContract(const std::string &symbol_asset_id);

    // Market Data:
    std::vector<TimeSeries> requestStockBars(std::vector<std::string> symbols,
                                             TimeFrame tframe = TimeFrame(15, TimeFrameUnit::Minute),
                                             Date start = Date::now() - std::chrono::days{1},
                                             std::optional<Date> end = std::nullopt,
                                             int limit = 100); // handles Interaction with StockBarsRequest Class
    std::vector<TimeSeriesPoint> requestStockBarsLatest(const std::vector<std::string> &symbols);
    std::vector<TimeSeries> requestOptionBars(std::vector<std::string> symbols,
                                              TimeFrame tframe,
                                              std::optional<std::string> start = std::nullopt,
                                              std::optional<std::string> end = std::nullopt,
                                              std::optional<int> limit = std::nullopt);
    std::vector<TimeSeriesPoint> requestOptionBarsLatest(const std::vector<std::string> &options);
    OptionChain requestOptionChains(std::string underlying_symbol);

    // Other Data:
    std::vector<float> getGreeks(const OptionChain &optchain);
    std::vector<float> getDeltas(const OptionChain &optchain);
    std::vector<float> getGammas(const OptionChain &optchain);
    std::vector<float> getVegas(const OptionChain &optchain);
    std::vector<float> getRhos(const OptionChain &optchain);
    std::vector<float> getThetas(const OptionChain &optchain);

private:
    TradingClient trading_client;
    OptionClient option_client;
    MarketClient market_client;
};