#include <strategies/deltahedge.hpp>
#include <cmath>

void DeltaHedge::run()
{
    std::vector<TimeSeriesPoint> latest_stock = market_.requestStockBarsLatest(std::vector<std::string>{symbol}); // retrieves latest point
    OptionChain optchain = market_.requestOptionChains(symbol);                                                   // retrieves option chain.

    // If Hedged Option isn't set
    if (!hedgedoption.has_value())
    {
        Date now = Date::now();
        float current_price = latest_stock.at(0).values["close"];
        Date date = now + std::chrono::days(90);
        float price = std::round((current_price + current_price * 0.1) / 100.0f) * 100.0f;
        hedgedoption = optchain.find_Option(symbol, date, 'C', price);
        };
};

void DeltaHedge::setSymbol(std::string symbol) { this->symbol = symbol; };
