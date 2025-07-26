#include <iostream>

#include <api/trading_client.hpp>
#include <env/env.hpp>
#include <http/http_client.hpp>
#include <trading/requests.hpp>
#include <memory>
#include <iostream>

TradingClient::TradingClient()
{
    init();
};

void TradingClient::init()
{
    // Keys
    auto [pub_key, priv_key] = get_env_keys();
    public_key = pub_key;
    private_key = priv_key;

    // HTTP Client
    http_client = std::make_shared<HTTPClient>(pub_key, priv_key, true);
}

void TradingClient::show_keys()
{
    std::cout << "Public Key:" << public_key << " Private Key:" << private_key << std::endl;
}

std::string TradingClient::submit_order(const Order &order_data)
{
    std::string extension = "/orders";
    std::string payload = order_data.to_fields();
    return http_client->POST(extension, payload);
};

// Core Positions
std::string TradingClient::get_all_positions()
{
    std::string extension = "/positions";
    return http_client->GET(extension);
};
std::string TradingClient::get_open_position(const std::string symbol_asset_id)
{
    std::string extension = "/positions/" + symbol_asset_id;
    return http_client->GET(extension);
};

std::string TradingClient::close_all_positions()
{
    std::string extention = "/positions";
    return http_client->DELETE(extention);
};

std::string TradingClient::close_position(const std::string symbol_asset_id)
{
    std::string extension = "/positions/" + symbol_asset_id;
    return http_client->DELETE(extension);
};

// Portfolio
std::string TradingClient::get_portfolio_history()
{
    std::string extension = "/account/portfolio/history";
    return http_client->GET(extension);
};

// Option Contracts
std::string TradingClient::get_option_contracts(GetOptionContractsRequest request)
{
    std::string extension = "/options/contracts";
    std::string parameters = request.to_fields();
    return http_client->GET(extension, parameters);
};
std::string TradingClient::get_option_contract(const std::string symbol_asset_id)
{
    std::string extension = "/options/contracts/" + symbol_asset_id;
    return http_client->GET(extension);
};