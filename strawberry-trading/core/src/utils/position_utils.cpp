#include <common/position.hpp>
#include <nlohmann/json.hpp>

Position parsePosition(const nlohmann::json &position_json)
{
    Position position;
    position.symbol = position_json["symbol"];
    position.asset_class = position_json["asset_class"];
    position.asset_marginable = position_json["asset_marginable"];
    position.qty = position_json["qty"];
    position.avg_entry_price = position_json["avg_entry_price"];
    position.side = position_json["side"];
    position.market_value = position_json["market_value"];
    position.cost_basis = position_json["cost_basis"];
    position.unrealized_pl = position_json["unrealized_pl"];
    position.unrealized_plpc = position_json["unrealized_plpc"];
    position.unrealized_intraday_pl = position_json["unrealized_intraday_pl"];
    position.unrealized_intraday_plpc = position_json["unrealized_intraday_plpc"];
    position.current_price = position_json["current_price"];
    position.lastday_price = position_json["lastday_price"];
    position.change_today = position_json["change_today"];
    position.qty_available = position_json["qty_available"];
    return position;
};
