#include <utils/enums.hpp>
#include <optional>
class Order
{
public:
    Order(std::string symbol,
          std::optional<float> qty = std::nullopt,
          std::optional<float> notional = std::nullopt,
          std::optional<OrderSide> side = std::nullopt,
          std::optional<OrderType> type = std::nullopt,
          std::optional<TimeInForce> time_in_force = std::nullopt,
          std::optional<OrderClass> orderclass = std::nullopt,
          std::optional<bool> extended_hours = std::nullopt,
          std::optional<std::string> client_order_id = std::nullopt);

    std::string symbol;
    std::optional<float> qty;
    std::optional<float> notional;
    std::optional<OrderSide> side;
    std::optional<OrderType> type;
    std::optional<TimeInForce> time_in_force;
    std::optional<OrderClass> orderclass;
    std::optional<bool> extended_hours;
    std::optional<std::string> client_order_id;
    // int legs; If Complex Options should be added
    std::string to_fields() const;
};