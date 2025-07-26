#include <api/trading_client.hpp>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    TradingClient client;
    std::vector<std::string> underlying_symbols = {"SPY"};
    GetOptionContractsRequest request = GetOptionContractsRequest(underlying_symbols);
    std::string output = client.get_all_positions();
    std::string options = client.get_option_contracts(request);
    std::cout << options << std::endl;
}