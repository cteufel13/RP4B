#pragma once
#include <http/http_client.hpp>
#include <utils/requests.hpp>

class OptionClient
{
public:
    OptionClient();
    // Basic Functions
    void init();
    std::string get_option_bars(const OptionBarRequest &optionbarrequest);
    std::string get_option_latest_bars(const OptionLatestBarRequest &optionbarlatestrequest);
    std::string get_options_chains(const OptionChainRequest &optionchainrequest);

private:
    std::string public_key;
    std::string private_key;
    std::shared_ptr<HTTPClient> http_client;
};