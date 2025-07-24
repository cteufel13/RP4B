#pragma once

#include <string>
#include <memory>
#include <http/http_client.hpp>

class AlpacaClient
{

public:
    AlpacaClient();
    // Basic Functions
    void init();
    void show_keys();

    // Order Positions
    std::string submit_order();

    // Core Positions
    std::string get_all_positions();
    std::string get_open_position(const std::string symbol_asset_id);
    std::string close_all_positions();
    std::string close_position();

    // Portfolio
    std::string get_portfolio_history();

    // Option Contracts
    std::string get_option_contracts();
    std::string get_option_contract();

private:
    std::string public_key;
    std::string private_key;
    std::shared_ptr<HTTPClient> http_client;
};