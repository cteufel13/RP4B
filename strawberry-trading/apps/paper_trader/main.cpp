#include <api/trading_client.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <scheduler/scheduler.hpp>
#include <thread>

void say_hello()
{
    std::cout << "HELLO!" << std::endl;
}

int main()
{
    // TradingClient client;
    // Order order = Order("SPY250728C00643000", 2.0, std::nullopt, OrderSide::BUY, OrderType::MARKET, TimeInForce::DAY, OrderClass::SIMPLE);
    // std::cout << client.submit_order(order) << std::endl;
    // std::vector<std::string> underlying = {"SPY"};
    // GetOptionContractsRequest options = GetOptionContractsRequest(underlying);
    // std::cout << client.get_option_contracts(options) << std::endl;
    Scheduler scheduler;
    scheduler.addTask(say_hello, std::chrono::seconds(10));
    std::thread sched_thread([&scheduler]()
                             { scheduler.run(); });

    std::this_thread::sleep_for(std::chrono::seconds(15)); // Let it run a bit
    std::cout << "[Main] Stopping scheduler...\n";
    scheduler.stop();

    sched_thread.join(); // Wait for thread to finish
    std::cout << "[Main] Done.\n";

    return 0;
}