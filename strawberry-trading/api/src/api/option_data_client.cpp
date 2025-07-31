#include <api/option_data_client.hpp>
#include <env/env.hpp>
#include <utils/requests.hpp>
#include <string>
#include <iostream>

OptionClient::OptionClient()
{
    init();
};

// Basic Functions
void OptionClient::init()
{
    auto [pub_key, priv_key] = get_env_keys();
    public_key = pub_key;
    private_key = priv_key;

    // HTTP Client
    http_client = std::make_shared<HTTPClient>(pub_key, priv_key, "https://data.alpaca.markets/v1beta1");
};
std::string OptionClient::get_option_bars(const OptionBarRequest &optionbarrequest)
{
    std::string extension = "/options/bars";
    std::string payload = optionbarrequest.to_fields();
    return http_client->GET(extension, payload);
};

std::string OptionClient::get_option_latest_bars(const OptionLatestBarRequest &optionbarlatestrequest)
{
    std::string extension = "/options/bars";
    std::string payload = optionbarlatestrequest.to_fields();
    return http_client->GET(extension, payload);
};

std::string OptionClient::get_options_chains(const OptionChainRequest &optionchainrequest)
{
    std::string extension = "/options/snapshots/" + optionchainrequest.symbol;
    std::string payload = optionchainrequest.to_fields();
    return http_client->GET(extension, payload);
};
