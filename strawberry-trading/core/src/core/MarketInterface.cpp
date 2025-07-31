#include <core/MarketInterface.hpp>
#include <nlohmann/json.hpp>
#include <logger_alias.hpp>
#include <string>
#include <iostream>

MarketInterface::MarketInterface() : trading_client(), option_client(), market_client() {};

bool MarketInterface::order(std::string symbol,
                            float qty,
                            std::optional<float> notional,
                            OrderSide side,
                            OrderType type,
                            TimeInForce time_in_force,
                            OrderClass orderclass,
                            bool extended_hours)
{

    Order order = Order(symbol,
                        qty,
                        notional,
                        side,
                        type,
                        time_in_force,
                        orderclass,
                        extended_hours);

    std::string response = trading_client.submit_order(order);
    nlohmann::json response_json = nlohmann::json::parse(response);

    if (response_json["filled_at"].is_null())
    {
        logger.warning("[MarketInterface::order] Order was not filled. May be after hours.");
        return false;
    }
    else
    {
        logger.info("[MarketInterface::order] Order was filled successfully at " + response_json["filled_at"].get<std::string>() + ".");
        return true;
    };
};

std::string MarketInterface::getAllPositions()
{
    std::string response = trading_client.get_all_positions();
    std::cout << response << std::endl;
};