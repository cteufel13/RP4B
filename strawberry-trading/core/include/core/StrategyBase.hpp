#pragma once

#include <core/MarketInterface.hpp>
#include <chrono>

class TradingStrategy
{
public:
    TradingStrategy(MarketInterface &market, std::chrono::seconds interval);
    virtual ~TradingStrategy() = default;

    virtual void run() = 0;
    std::chrono::seconds getInterval();

protected:
    MarketInterface &market_;
    std::chrono::seconds interval;
};
