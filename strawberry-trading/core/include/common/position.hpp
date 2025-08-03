#pragma once
#include <string>

enum class ActionType
{
    BUY,
    SELL,
    HOLD
};

struct Position
{

    Position();

    Position(const std::string &sym,
             const std::string &assetCls,
             bool marginable,
             float quantity,
             float entry_price,
             const std::string &position_side);

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

    void update(ActionType action, float qty_change, float price);
};
