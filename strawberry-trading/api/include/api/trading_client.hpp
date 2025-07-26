#pragma once

#include <string>
#include <memory>
#include <http/http_client.hpp>
#include <trading/order.hpp>
#include <trading/requests.hpp>

class TradingClient
{

public:
    TradingClient();
    // Basic Functions
    void init();
    void show_keys();

    // Order Positions
    std::string submit_order(const Order &order_data);

    // Core Positions
    std::string get_all_positions();
    std::string get_open_position(const std::string symbol_asset_id);
    std::string close_all_positions();
    std::string close_position(const std::string symbol_asset_id);

    // Portfolio
    std::string get_portfolio_history();

    // Option Contracts
    std::string get_option_contracts(GetOptionContractsRequest request);
    std::string get_option_contract(const std::string symbol_asset_id);

private:
    std::string public_key;
    std::string private_key;
    std::shared_ptr<HTTPClient> http_client;
};