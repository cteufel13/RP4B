#include <utils/enums.hpp>
#include <string>

std::string type2string(OrderType type)
{
    switch (type)
    {
    case OrderType::MARKET:
        return "market";

    case OrderType::LIMIT:
        return "limit";

    case OrderType::STOP:
        return "stop";
    case OrderType::STOP_LIMIT:
        return "stop_limit";
    case OrderType::TRAILING_STOP:
        return "trailing_stop";
    }
};

std::string tif2string(TimeInForce tif)
{
    switch (tif)
    {
    case TimeInForce::DAY:
        return "day";
    case TimeInForce::GTC:
        return "gtc";
    case TimeInForce::OPG:
        return "opg";
    case TimeInForce::CLS:
        return "cls";
    case TimeInForce::IOC:
        return "ioc";
    case TimeInForce::FOK:
        return "fok";
    }
};

std::string class2string(OrderClass orderclass)
{
    switch (orderclass)
    {
    case OrderClass::SIMPLE:
        return "simple";
    case OrderClass::MLEG:
        return "mleg";
    case OrderClass::BRACKET:
        return "BRACKET";
    case OrderClass::OCO:
        return "oco";
    case OrderClass::OTO:
        return "oto";
    }
};

std::string side2string(OrderSide side)
{
    switch (side)
    {
    case OrderSide::BUY:
        return "buy";
    case OrderSide::SELL:
        return "sell";
    }
};

std::string contract2string(ContractType type)
{
    switch (type)
    {
    case ContractType::CALL:
        return "call";
    case ContractType::PUT:
        return "put";
    }
};