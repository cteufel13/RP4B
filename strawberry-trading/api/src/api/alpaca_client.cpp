#include <iostream>

#include <api/alpaca_client.hpp>
#include <env/env.hpp>

AlpacaClient::AlpacaClient()
{
    init();
};

void AlpacaClient::init()
{
    auto [pub_key, priv_key] = get_env_keys();
    public_key = pub_key;
    private_key = priv_key;
}

void AlpacaClient::show_keys()
{
    std::cout << "Public Key:" << public_key << " Private Key:" << private_key << std::endl;
}