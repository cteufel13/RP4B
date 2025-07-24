#ifndef ORDERTYPES_H
#define ORDERTYPES_H

#include <string>

class OrderType
{
public:
    static const std::string MARKET;
    static const std::string LIMIT;
    static const std::string STOP;
    static const std::string STOP_LIMIT;
    static const std::string TRAILING_STOP;
};

class TimeInForce
{
public:
    static const std::string DAY;
    static const std::string GTC;
    static const std::string OPG;
    static const std::string CLS;
    static const std::string IOC;
    static const std::string FOK;
};

class OrderClass
{
public:
    static const std::string SIMPLE;
    static const std::string MLEG;
    static const std::string BRACKET;
    static const std::string OCO;
    static const std::string OTO;
};

#endif // ORDERTYPES_H
