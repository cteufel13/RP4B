#pragma once

#include <string>

class AlpacaClient
{

public:
    void init();
    AlpacaClient();

    void show_keys();

private:
    std::string public_key;
    std::string private_key;
};