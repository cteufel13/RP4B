#include <string>
#include <enums.hpp>

class Order
{
public:
    std::string symbol;
    float qty;
    float notional;
    OrderType type;
    TimeInForce time_in_force;
    OrderClass orderclass;
    bool extended_hours;
    std::string client_order_id;
    // int legs; If Complex Options should be added
};
