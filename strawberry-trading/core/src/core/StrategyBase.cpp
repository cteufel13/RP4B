#include <core/StrategyBase.hpp>

TradingStrategy::TradingStrategy(MarketInterface &market, std::chrono::seconds interval)
    : market_(market), interval(interval) {};

std::chrono::seconds TradingStrategy::getInterval()
{
    return interval;
}
