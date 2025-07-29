#include <utils/order.hpp>
#include <optional>
#include <iostream>
#include <nlohmann/json.hpp>

Order::Order(std::string symbol,
             std::optional<float> qty,
             std::optional<float> notional,
             std::optional<OrderSide> side,
             std::optional<OrderType> type,
             std::optional<TimeInForce> time_in_force,
             std::optional<OrderClass> orderclass,
             std::optional<bool> extended_hours,
             std::optional<std::string> client_order_id)
    : symbol(std::move(symbol)),
      qty(std::move(qty)),
      notional(std::move(notional)),
      side(std::move(side)),
      type(std::move(type)),
      time_in_force(std::move(time_in_force)),
      orderclass(std::move(orderclass)),
      extended_hours(std::move(extended_hours)),
      client_order_id(std::move(client_order_id))
{
}

std::string Order::to_fields() const
{
    nlohmann::json j;
    j["symbol"] = symbol;

    if (qty.has_value())
        j["qty"] = qty.value();
    if (notional.has_value())
        j["notional"] = notional.value();
    if (side.has_value())
        j["side"] = side2string(side.value());
    if (type.has_value())
        j["type"] = type2string(type.value());
    if (time_in_force.has_value())
        j["time_in_force"] = tif2string(time_in_force.value());
    if (orderclass.has_value())
        j["order_class"] = class2string(orderclass.value());
    if (extended_hours.has_value())
        j["extended_hours"] = extended_hours.value();
    if (client_order_id.has_value())
        j["client_order_id"] = client_order_id.value();

    return j.dump();
}