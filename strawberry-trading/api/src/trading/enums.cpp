#include <trading/enums.hpp>
#include <string>

const std::string OrderType::MARKET = "market";
const std::string OrderType::LIMIT = "limit";
const std::string OrderType::STOP = "stop";
const std::string OrderType::STOP_LIMIT = "stop_limit";
const std::string OrderType::TRAILING_STOP = "trailing_stop";

const std::string TimeInForce::DAY = "day";
const std::string TimeInForce::GTC = "gtc";
const std::string TimeInForce::OPG = "opg";
const std::string TimeInForce::CLS = "cls";
const std::string TimeInForce::IOC = "ioc";
const std::string TimeInForce::FOK = "fok";

const std::string OrderClass::SIMPLE = "simple";
const std::string OrderClass::MLEG = "mleg";
const std::string OrderClass::BRACKET = "bracket";
const std::string OrderClass::OCO = "oco";
const std::string OrderClass::OTO = "oto";
