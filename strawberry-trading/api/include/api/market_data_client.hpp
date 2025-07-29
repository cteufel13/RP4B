#pragma once
#include <http/http_client.hpp>
#include <utils/requests.hpp>
class MarketClient
{
public:
    MarketClient();
    // Basic Functions
    void init();

    //
    std::string get_stock_bars(const StockBarsRequest &stockbarsrequest);
    std::string get_latest_bars(const StockLatestBarRequest &stockbarslatestrequest);

private:
    std::string public_key;
    std::string private_key;
    std::shared_ptr<HTTPClient> http_client;
};