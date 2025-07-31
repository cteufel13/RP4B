#pragma once
#include <string>
#include <optional>

struct Option
{
    std::string ticker;
    std::string date;
    char type;
    double strike;

    std::optional<double> premium;
    std::optional<int> volume;
    std::optional<int> openInterest;
    std::optional<double> impliedVol;
    std::optional<double> delta, gamma, theta, vega, rho;
    std::optional<std::string> style = "American";
    std::optional<int> multiplier = 100;
};