#include <common/option.hpp>
#include <utils/option_utils.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

Option parseOptionName(const std::string &optionName)
{
    Option data;
    data.ticker = optionName.substr(0, optionName.size() - 15);
    data.date = Date::from_string("20" + optionName.substr(optionName.size() - 15, 6)); // YYMMDD → 20YYMMDD
    data.type = optionName[optionName.size() - 9];
    int strikeInt = std::stoi(optionName.substr(optionName.size() - 8));
    data.strike = strikeInt / 1000.0;
    return data;
};

void parseGreeks(const nlohmann::json &greeksjson, Option &option)
{
    option.delta = greeksjson["delta"];
    option.gamma = greeksjson["gamma"];
    option.vega = greeksjson["vega"];
    option.rho = greeksjson["rho"];
    option.theta = greeksjson["theta"];
};

void parseVolume(const nlohmann::json &greeksjson, Option &option)
{
    option.volume = greeksjson["v"];
};

Option parseOption(const nlohmann::json &optionjson)
{
    Option option = parseOptionName(optionjson["symbol"]);
    option.status = optionjson["status"];
    option.tradable = optionjson["tradable"];
    option.date = Date::from_string(optionjson["expiration_date"]);
    option.root = optionjson["root_symbol"];
    option.multiplier = std::stoi(optionjson["multiplier"].get<std::string>());
    option.size = std::stoi(optionjson["size"].get<std::string>());

    return option;
};