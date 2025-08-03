#include <api/trading_client.hpp>
#include <api/market_data_client.hpp>
#include <api/option_data_client.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <scheduler/scheduler.hpp>
#include <logger_alias.hpp>
#include <utils/json.hpp>
#include <thread>
#include <common/optionchain.hpp>
#include <core/MarketInterface.hpp>
#include <strategies/deltahedge.hpp>

int main()
{
    Scheduler scheduler;
    MarketInterface marketinterface;
    logger.set_log_file("Run.log");

    DeltaHedge strat = DeltaHedge(marketinterface, std::chrono::seconds(100));
    strat.setSymbol("SPY");
    strat.run();

    return 0;
}