#pragma once
#include <string>

struct Position
{
    std::string symbol;
    std::string asset_class;
    bool asset_marginable;
    float qty;
    float avg_entry_price;
    std::string side;
    float market_value;
    float cost_basis;
    float unrealized_pl;
    float unrealized_plpc;
    float unrealized_intraday_pl;
    float unrealized_intraday_plpc;
    float current_price;
    float lastday_price;
    float change_today;
    int qty_available;
};
