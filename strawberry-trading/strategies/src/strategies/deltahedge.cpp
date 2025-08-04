#include <strategies/deltahedge.hpp>
#include <cmath>
#include <logger_alias.hpp>

void DeltaHedge::run()
{
    if (!is_valid_time())
    {
        logger.info("[DeltaHedge::run] Time is not within trading hours");
        return;
    }

    if (!initialized)
    {
        init();
    }
    else
    {
        OptionChain current_option_chain = market_.requestOptionChains(symbol, typeconv(hedgedoption.value().type), hedgedoption.value().strike, hedgedoption.value().strike, hedgedoption.value().date.to_string());
        std::vector<TimeSeriesPoint> current_prices = market_.requestStockBarsLatest(std::vector<std::string>{symbol});
        Option current_option = current_option_chain.find_Option(symbol, hedgedoption.value().date, hedgedoption.value().type, hedgedoption.value().strike);

        float current_stock_price = current_prices.at(0).values["close"];
        float current_delta = current_option.delta.value();
        float stock_position = positions.at(0).qty;

        float stock_to_move = -1 * stock_position - current_delta;

        if (stock_to_move < 0)
        {
            stock_to_move *= -1;
            // market_.order(symbol, stock_to_move, std::nullopt, OrderSide::SELL);
            positions.at(0).update(ActionType::SELL, std::abs(stock_to_move), current_stock_price);
        }
        else if (stock_to_move > 0)
        {
            // market_.order(symbol, stock_to_move, std::nullopt, OrderSide::BUY);
            positions.at(0).update(ActionType::BUY, std::abs(stock_to_move), current_stock_price);
        }
        else
        {
            positions.at(0).update(ActionType::HOLD, 0, current_stock_price);
        };
        positions.at(1).update(ActionType::HOLD, 0, current_option.premium.value());
    };
};

void DeltaHedge::setSymbol(std::string symbol) { this->symbol = symbol; };

void DeltaHedge::init()
{

    std::vector<TimeSeriesPoint> init_stock = market_.requestStockBarsLatest(std::vector<std::string>{symbol});
    OptionChain init_optchain = market_.requestOptionChains(symbol);
    float init_stock_price = init_stock.at(0).values["close"];

    setHedgedOoption(init_optchain, init_stock_price);
    double init_delta = hedgedoption.value().delta.value();

    // market_.order(hedgedoption.value().name, 1);
    // market_.order(symbol, init_delta, std::nullopt, OrderSide::SELL);

    Position stock_pos = Position(symbol, "stock", true, -1 * init_delta, init_stock_price, "short");
    Position option_pos = Position(hedgedoption.value().name, "option", true, 1.0, hedgedoption.value().premium.value(), "long");

    positions.push_back(stock_pos);
    positions.push_back(option_pos);

    initialized = true;
};

void DeltaHedge::setHedgedOoption(OptionChain &optchain, float price)
{
    Date now = Date::now();
    Date date = now + std::chrono::days(90);
    float strike_price = std::round((price + price * 0.1) / 100.0f) * 100.0f;
    hedgedoption = optchain.find_Option(symbol, date, 'C', strike_price);
    logger.info("[Delta Hedge Strategy] Selected following option to hedge:  Symbol:" + symbol + " Date:" + date.to_string() + " Type:C" + " Strike:" + std::to_string(price));
}

ContractType DeltaHedge::typeconv(const char &type)
{
    if (type == 'C')
    {
        return ContractType::CALL;
    }
    else if (type == 'P')
    {
        return ContractType::PUT;
    };
};

bool DeltaHedge::is_valid_time()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm *local_time = std::localtime(&now);

    int current_minutes = local_time->tm_hour * 60 + local_time->tm_min;
    int start_minutes = 9 * 60 + 30;
    int end_minutes = 16 * 60 + 30;

    return current_minutes >= start_minutes && current_minutes <= end_minutes;
}