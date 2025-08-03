#pragma once
#include <string>
#include <vector>
#include <common/option.hpp>

class OptionChain
{
public:
    OptionChain(std::string optionchainjstring);
    std::vector<std::vector<float>> get_greeks_matrix();
    std::vector<float> get_deltas();
    std::vector<float> get_gammas();
    std::vector<float> get_vegas();
    std::vector<float> get_rhos();
    std::vector<float> get_thetas();
    Option find_Option(const std::string &ticker,
                       const Date &date,
                       const char &type,
                       const double &strike);

    friend std::ostream &operator<<(std::ostream &os, const OptionChain &obj);

private:
    void process(const std::string &optionchainjstring);
    std::vector<Option> options;
    std::vector<std::vector<float>> greeks;
};