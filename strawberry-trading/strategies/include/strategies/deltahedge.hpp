#include <core/StrategyBase.hpp>
#include <chrono>
#include <string>
#include <optional>

class DeltaHedge : private TradingStrategy
{
public:
    DeltaHedge(MarketInterface &market_, std::chrono::seconds interval)
        : TradingStrategy(market_, interval) {};

    void run() override;

    void setSymbol(std::string symbol);

private:
    std::chrono::seconds interval;
    float prev_delta;

    std::string symbol;
    std::optional<Option> hedgedoption;
};