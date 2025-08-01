#pragma once
#include <string>
#include <optional>
#include <utils/timeseries_utils.hpp>

struct Option
{
    std::string ticker;
    Date date;
    char type;
    double strike;

    std::optional<std::string> root;

    std::optional<double> premium;
    std::optional<int> volume;
    std::optional<int> openInterest;
    std::optional<double> impliedVol;
    std::optional<double> delta, gamma, theta, vega, rho;
    std::optional<std::string> status = "active";
    std::optional<bool> tradable = true;
    std::optional<std::string> style = "American";
    std::optional<int> multiplier = 100;
    std::optional<int> size = 100;
};