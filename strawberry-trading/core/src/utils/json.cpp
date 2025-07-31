#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <utils/json.hpp>

void savejson(const std::string &jsonstring, const std::string &filename)
{
    nlohmann::json j = nlohmann::json::parse(jsonstring);
    std::ofstream o(filename);
    o << j.dump(4);
};
