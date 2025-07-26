#pragma once

#include <string>
#include <map>
#include <optional>
#include <vector>
#include <trading/enums.hpp>

class GetOptionContractsRequest
{
public:
    GetOptionContractsRequest(
        std::optional<std::vector<std::string>> underlying_symbols = std::nullopt,
        std::optional<AssetStatus> status = AssetStatus::ACTIVE,
        std::optional<std::string> expiration_date = std::nullopt,
        std::optional<std::string> expiration_date_gte = std::nullopt,
        std::optional<std::string> expiration_date_lte = std::nullopt,
        std::optional<std::string> root_symbol = std::nullopt,
        std::optional<ContractType> type = std::nullopt,
        std::optional<ExerciseStyle> style = ExerciseStyle::AMERICAN,
        std::optional<std::string> strike_price_gte = std::nullopt,
        std::optional<std::string> strike_price_lte = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<std::string> page_token = std::nullopt);

    std::optional<std::vector<std::string>> underlying_symbols;
    std::optional<AssetStatus> status = AssetStatus::ACTIVE;
    std::optional<std::string> expiration_date;
    std::optional<std::string> expiration_date_gte;
    std::optional<std::string> expiration_date_lte;
    std::optional<std::string> root_symbol;
    std::optional<ContractType> type;
    std::optional<ExerciseStyle> style;
    std::optional<std::string> strike_price_gte;
    std::optional<std::string> strike_price_lte;
    std::optional<int> limit;
    std::optional<std::string> page_token;

    std::string to_fields();
};