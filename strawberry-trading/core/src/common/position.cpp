#include <common/position.hpp>
#include <logger_alias.hpp>

Position::Position()
    : symbol(""), asset_class(""), asset_marginable(false),
      qty(0), avg_entry_price(0), side("none"),
      market_value(0), cost_basis(0),
      unrealized_pl(0), unrealized_plpc(0),
      unrealized_intraday_pl(0), unrealized_intraday_plpc(0),
      current_price(0), lastday_price(0),
      change_today(0), qty_available(0) {
      };

Position::Position(const std::string &sym,
                   const std::string &assetCls,
                   bool marginable,
                   float quantity,
                   float entry_price,
                   const std::string &position_side)
    : symbol(sym),
      asset_class(assetCls),
      asset_marginable(marginable),
      qty(quantity),
      avg_entry_price(entry_price),
      side(position_side),
      current_price(entry_price), // start = entry price
      lastday_price(0),           // no previous day's price
      unrealized_pl(0),
      unrealized_plpc(0),
      unrealized_intraday_pl(0),
      unrealized_intraday_plpc(0),
      change_today(0){

          {cost_basis = qty * avg_entry_price;
market_value = cost_basis;
qty_available = static_cast<int>(qty);
}
}
;

void Position::update(ActionType action, float qty_change, float price)
{
    // HOLD: Just update market value and P/L
    if (action == ActionType::HOLD)
    {
        current_price = price;
        market_value = qty * current_price;
        unrealized_pl = market_value - cost_basis;
        unrealized_plpc = (cost_basis != 0) ? (unrealized_pl / cost_basis) : 0;
        return;
    }

    // --- BUY LOGIC ---
    if (action == ActionType::BUY)
    {
        float total_cost_before = cost_basis;
        float total_qty_before = qty;

        qty += qty_change;
        qty_available = static_cast<int>(qty);
        cost_basis += qty_change * price;

        avg_entry_price = (total_cost_before + (qty_change * price)) / qty;

        current_price = price;
        market_value = qty * current_price;
        unrealized_pl = market_value - cost_basis;
        unrealized_plpc = (cost_basis != 0) ? (unrealized_pl / cost_basis) : 0;

        return;
    }

    // --- SELL LOGIC ---
    if (action == ActionType::SELL)
    {

        float cost_per_share = avg_entry_price;
        float cost_reduction = cost_per_share * qty_change;

        float realized_pl = (price - cost_per_share) * qty_change;

        qty -= qty_change;
        qty_available = static_cast<int>(qty);
        cost_basis -= cost_reduction;

        if (qty == 0)
        {
            avg_entry_price = 0;
            market_value = 0;
            cost_basis = 0;
            unrealized_pl = 0;
            unrealized_plpc = 0;
        }
        else
        {
            current_price = price;
            market_value = qty * current_price;
            unrealized_pl = market_value - cost_basis;
            unrealized_plpc = (cost_basis != 0) ? (unrealized_pl / cost_basis) : 0;
        }

        return;
    }
};