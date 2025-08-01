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
    std::string requestStockBars();       // handles Interaction with StockBarsRequest Class
    std::string requestStockBarsLatest(); // handles Interaction with StockbarsLatest Class
    std::string requestOptionBars();
    std::string requestOptionBarsLatest();
    OptionChain requestOptionChains();

    // Other Data:
    void getGreeks(const OptionChain &optchain);
    void getDeltas(const OptionChain &optchain);
    void getGammas(const OptionChain &optchain);
    void getVegas(const OptionChain &optchain);
    void getRhos(const OptionChain &optchain);
    void getRhetas(const OptionChain &optchain);

private:
    TradingClient trading_client;
    OptionClient option_client;
    MarketClient market_client;
};