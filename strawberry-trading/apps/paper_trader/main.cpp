#include <iostream>
#include <scheduler/scheduler.hpp>
#include <logger_alias.hpp>
#include <thread>
#include <core/MarketInterface.hpp>
#include <strategies/deltahedge.hpp>

int main()
{

    Scheduler scheduler;
    MarketInterface marketinterface;

    logger.set_log_file("logs/run.log");

    DeltaHedge strat = DeltaHedge(marketinterface, std::chrono::seconds(100));
    strat.setSymbol("SPY");

    scheduler.addTask([&strat]()
                      { strat.run(); }, strat.getInterval());

    std::thread sched_thread([&scheduler]()
                             { scheduler.run(); });

    std::cin.get(); // Main thread waits for Enter

    std::cout << "[Main] Stopping scheduler...\n";
    scheduler.stop();

    sched_thread.join();
    std::cout << "[Main] Done.\n";

    return 0;
}