#include <api/market_data_client.hpp>
#include <env/env.hpp>
#include <utils/requests.hpp>
#include <string>
#include <iostream>

MarketClient::MarketClient()
{
    init();
};

// Basic Functions
void MarketClient::init()
{
    auto [pub_key, priv_key] = get_env_keys();
    public_key = pub_key;
    private_key = priv_key;

    // HTTP Client
    http_client = std::make_shared<HTTPClient>(pub_key, priv_key, "https://data.alpaca.markets/v2");
};

//
std::string MarketClient::get_stock_bars(const StockBarsRequest &stockbarsrequest)
{
    std::string extension = "/stocks/bars";
    std::string payload = stockbarsrequest.to_fields();
    return http_client->GET(extension, payload);
};
std::string MarketClient::get_stock_latest_bars(const StockLatestBarRequest &stockbarslatestrequest)
{
    std::string extension = "/stocks/bars/latest";
    std::string payload = stockbarslatestrequest.to_fields();
    return http_client->GET(extension, payload);
};
