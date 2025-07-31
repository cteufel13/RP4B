#include <api/market_data_client.hpp>
#include <api/option_data_client.hpp>
#include <api/trading_client.hpp>
#include <common/optionchain.hpp>
#include <common/option.hpp>
#include <utils/json.hpp>

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
    std::string getAllPositions();
    std::string getOpenPosition();
    std::string closeAllPositions();
    std::string closePosition();
    std::string getPortfolioHistory();
    std::string getOptionContracts();
    std::string getOptionContract();

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