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

void say_hello()
{
    std::cout << "HELLO!" << std::endl;
}

void say_bingbong()
{
    std::cout << "BING BONG" << std::endl;
}

int main()
{
    // TradingClient client;
    // Order order = Order("SPY", 2.0, std::nullopt, OrderSide::BUY, OrderType::MARKET, TimeInForce::DAY, OrderClass::SIMPLE);
    // std::cout << client.submit_order(order) << std::endl;
    // std::vector<std::string> underlying = {"SPY"};
    // GetOptionContractsRequest options = GetOptionContractsRequest(underlying);
    // std::cout << client.get_option_contracts(options) << std::endl;

    // Scheduler scheduler;
    // scheduler.addTask(say_hello, std::chrono::seconds(20));
    // scheduler.addTask(say_bingbong, std::chrono::seconds(10));
    // std::thread sched_thread([&scheduler]()
    //                          { scheduler.run(); });

    // std::cout << "Press any button to cancel..." << std::endl;
    // std::cin.get();
    // std::cout << "[Main] Stopping scheduler...\n";
    // scheduler.stop();

    // sched_thread.join(); // Wait for thread to finish
    // std::cout << "[Main] Done.\n";

    // logger.set_log_file("log.txt");
    // logger.info("starting the paper trader");
    // std::vector<std::string> symbols = {"AAPL"};
    // MarketClient client;
    // OptionLatestBarRequest req = OptionLatestBarRequest(symbols);
    // std::cout << client.get_option_latest_bars(req) << std::endl;
    // OptionChainRequest req = OptionChainRequest("AAPL");
    // OptionClient client;

    // std::string options_chain = client.get_options_chains(req);

    // OptionChain chain = OptionChain(options_chain);
    // auto greeks = chain.get_greeks_matrix();

    // savejson(options_chain, "OptionsChains.txt");

    MarketInterface marketinterface = MarketInterface();
    marketinterface.getAllPositions();

    return 0;
}