#include <common/optionchain.hpp>
#include <common/option.hpp>
#include <utils/option_utils.hpp>
#include <logger_alias.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

OptionChain::OptionChain(std::string optionchainjstring)
{
    process(optionchainjstring);
};

bool option_has_greeks(nlohmann::json optionjson)
{
    return optionjson.contains("greeks");
}

void OptionChain::process(const std::string &optionchainjstring)
{

    nlohmann::json j = nlohmann::json::parse(optionchainjstring);

    if (!j.contains("snapshots"))
    {
        logger.error("[OptionChain::process] \"snapshots\" can't be found in jsonstring, likely Alpaca issue.");
    }
    else
    {
        j = j["snapshots"];

        logger.info("[OptionChain::process] Processing " + std::to_string(j.size()) + " valid options");

        // Filter Option if has greeks or not
        for (auto it = j.begin(); it != j.end();)
        {
            if ((!option_has_greeks(it.value())) || !it.value().contains("dailyBar"))
            {
                it = j.erase(it);
            }
            else
            {
                ++it;
            }
        };

        for (auto &[key, value] : j.items())
        {
            Option option = parseOptionName(key);
            parseGreeks(value["greeks"], option);
            option.impliedVol = value["impliedVolatility"];
            parseVolume(value["dailyBar"], option);
            options.push_back(option);
        };
    };
};

std::vector<std::vector<float>> OptionChain::get_greeks_matrix()
{
    logger.info("OptionChain::get_greeks_matrix] Retrieving Greeks");
    std::vector<std::vector<float>> greeks;
    greeks.push_back(get_deltas());
    greeks.push_back(get_gammas());
    greeks.push_back(get_vegas());
    greeks.push_back(get_rhos());
    greeks.push_back(get_thetas());
    return greeks;
};
std::vector<float> OptionChain::get_deltas()
{
    std::vector<float> deltas;
    deltas.reserve(options.size());
    for (const auto &opt : options)
    {
        deltas.push_back(*opt.delta);
    }
    return deltas;
};
std::vector<float> OptionChain::get_gammas()
{
    std::vector<float> gammas;
    gammas.reserve(options.size());
    for (const auto &opt : options)
    {
        gammas.push_back(*opt.gamma);
    }
    return gammas;
};
std::vector<float> OptionChain::get_vegas()
{
    std::vector<float> vegas;
    vegas.reserve(options.size());
    for (const auto &opt : options)
    {
        vegas.push_back(*opt.vega);
    }
    return vegas;
};
std::vector<float> OptionChain::get_rhos()
{
    std::vector<float> rhos;
    rhos.reserve(options.size());
    for (const auto &opt : options)
    {
        rhos.push_back(*opt.rho);
    }
    return rhos;
};
std::vector<float> OptionChain::get_thetas()
{
    std::vector<float> thetas;
    thetas.reserve(options.size());
    for (const auto &opt : options)
    {
        thetas.push_back(*opt.theta);
    }
    return thetas;
};

Option OptionChain::find_Option(const std::string &ticker,
                                const Date &date,
                                const char &type,
                                const double &strike)
{

    Option bestMatch;
    Date minDate = Date::max(); // assume Date::max() gives the latest possible date
    double minStrikeDiff = std::numeric_limits<double>::max();

    for (const auto &option : options)
    {
        if (option.ticker != ticker || option.type != type)
            continue;

        if (option.date >= date)
        {
            if (option.date < minDate)
            {
                minDate = option.date;
                minStrikeDiff = std::abs(option.strike - strike);
                bestMatch = option;
            }
            else if (option.date == minDate)
            {
                double strikeDiff = std::abs(option.strike - strike);
                if (strikeDiff < minStrikeDiff)
                {
                    minStrikeDiff = strikeDiff;
                    bestMatch = option;
                }
            }
        }
    }

    return bestMatch;
};

std::ostream &operator<<(std::ostream &os, const OptionChain &obj)
{
    for (const auto &opt : obj.options)
    {
        os << "Ticker:" << opt.ticker << " Date:" << opt.date << " Type:" << opt.type << " Strike:" << opt.strike << " Delta:" << opt.delta.value() << " Gamma:" << opt.gamma.value() << " Vega:" << opt.vega.value() << std::endl;
    }
    return os;
}
