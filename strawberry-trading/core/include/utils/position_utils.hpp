#include <common/position.hpp>
#include <nlohmann/json.hpp>
#include <string>

Position parsePosition(const nlohmann::json &position_json);