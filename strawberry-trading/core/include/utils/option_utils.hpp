#include <common/option.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

Option parseOptionName(const std::string &optionName);

void parseGreeks(const nlohmann::json &greeksjson, Option &option);

void parseVolume(const nlohmann::json &greeksjson, Option &option);
