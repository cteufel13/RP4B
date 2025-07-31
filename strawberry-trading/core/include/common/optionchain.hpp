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

private:
    void process(const std::string &optionchainjstring);
    std::vector<Option> options;
    std::vector<std::vector<float>> greeks;
};