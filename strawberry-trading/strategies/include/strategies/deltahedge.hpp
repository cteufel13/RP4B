#include <core/StrategyBase.hpp>
#include <chrono>
#include <string>
#include <optional>

class DeltaHedge : private TradingStrategy
{
public:
    DeltaHedge(MarketInterface &market_, std::chrono::seconds interval)
        : TradingStrategy(market_, interval) {};

    void init();
    void run() override;
    void setHedgedOoption(OptionChain &optchain, float price);

    void setSymbol(std::string symbol);
    std::chrono::seconds interval;

private:
    float prev_delta;

    std::string symbol;
    std::optional<Option> hedgedoption;
    std::vector<Position> positions;
    bool initialized = false;

    ContractType typeconv(const char &type);
};
