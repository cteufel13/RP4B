#include <api/option_data_client.hpp>
#include <env/env.hpp>
#include <utils/requests.hpp>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

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
    std::string response = http_client->GET(extension, payload);

    nlohmann::json j = nlohmann::json::parse(response);
    nlohmann::json final_result;
    final_result["snapshots"] = nlohmann::json::object(); // initialize as dict

    if (j.contains("snapshots") && j["snapshots"].is_object())
    {
        for (auto &[key, value] : j["snapshots"].items())
        {
            final_result["snapshots"][key] = value;
        }
    }

    while (j.contains("next_page_token") && !j["next_page_token"].is_null())
    {
        std::string next_token = j["next_page_token"];
        std::string next_payload = payload + "&page_token=" + next_token;
        std::string next_response = http_client->GET(extension, next_payload);
        j = nlohmann::json::parse(next_response);

        if (j.contains("snapshots") && j["snapshots"].is_object())
        {
            for (auto &[key, value] : j["snapshots"].items())
            {
                final_result["snapshots"][key] = value;
            }
        }
    }
    final_result["next_page_token"] = nullptr;

    std::string output = final_result.dump();

    return output;
};
