#ifndef ORDERTYPES_H
#define ORDERTYPES_H

#include <string>

enum class OrderType
{
    MARKET,
    LIMIT,
    STOP,
    STOP_LIMIT,
    TRAILING_STOP,
};

enum class TimeInForce
{
    DAY,
    GTC,
    OPG,
    CLS,
    IOC,
    FOK,
};

enum class OrderClass
{
    SIMPLE,
    MLEG,
    BRACKET,
    OCO,
    OTO,
};

enum class OrderSide
{
    BUY,
    SELL,
};

enum class AssetStatus
{
    ACTIVE,
    INACTIVE,

};

enum class ContractType
{
    CALL,
    PUT
};

enum class ExerciseStyle
{
    AMERICAN,
    EUROPEAN
};

std::string type2string(OrderType type);
std::string tif2string(TimeInForce tif);
std::string class2string(OrderClass orderclass);
std::string side2string(OrderSide side);

#endif // ORDERTYPES_H
