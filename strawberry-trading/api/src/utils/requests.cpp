#include <string>
#include <map>
#include <optional>
#include <vector>
#include <utils/enums.hpp>
#include <utils/requests.hpp>
#include <utils/data.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

std::string to_query_string(std::string jstring)
{
    std::string json_string = jstring.substr(1, jstring.length() - 2); // removes outer {}
    std::string result;

    bool insideBrackets = false;

    for (char c : json_string)
    {
        if (c == '[')
        {
            insideBrackets = true;
            result += c;
        }
        else if (c == ']')
        {
            insideBrackets = false;
            result += c;
        }
        else if (c == ',' && !insideBrackets)
        {
            result += '&';
        }
        else if (c == ',' && insideBrackets)
        {
            result += "%2C";
        }
        else
        {
            result += c;
        }
    }

    // Replace ':' with '='
    std::replace(result.begin(), result.end(), ':', '=');

    // Remove quotes, brackets
    result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '['), result.end());
    result.erase(std::remove(result.begin(), result.end(), ']'), result.end());

    return result;
};

std::string to_string(AssetStatus status)
{
    switch (status)
    {
    case AssetStatus::ACTIVE:
        return "active";
    case AssetStatus::INACTIVE:
        return "inactive";
    }
    return "";
};

std::string to_string(ContractType type)
{
    switch (type)
    {
    case ContractType::CALL:
        return "call";
    case ContractType::PUT:
        return "put";
    }
    return "";
};

std::string to_string(ExerciseStyle style)
{
    switch (style)
    {
    case ExerciseStyle::AMERICAN:
        return "american";
    case ExerciseStyle::EUROPEAN:
        return "european";
    }
    return "";
};

GetOptionContractsRequest::GetOptionContractsRequest(
    std::optional<std::vector<std::string>> underlying_symbols,
    std::optional<AssetStatus> status,
    std::optional<std::string> expiration_date,
    std::optional<std::string> expiration_date_gte,
    std::optional<std::string> expiration_date_lte,
    std::optional<std::string> root_symbol,
    std::optional<ContractType> type,
    std::optional<ExerciseStyle> style,
    std::optional<std::string> strike_price_gte,
    std::optional<std::string> strike_price_lte,
    std::optional<int> limit,
    std::optional<std::string> page_token)
    : underlying_symbols(std::move(underlying_symbols)),
      status(status),
      expiration_date(std::move(expiration_date)),
      expiration_date_gte(std::move(expiration_date_gte)),
      expiration_date_lte(std::move(expiration_date_lte)),
      root_symbol(std::move(root_symbol)),
      type(type),
      style(style),
      strike_price_gte(std::move(strike_price_gte)),
      strike_price_lte(std::move(strike_price_lte)),
      limit(limit),
      page_token(std::move(page_token)) {};

std::string GetOptionContractsRequest::to_fields() const
{
    nlohmann::json j;

    if (underlying_symbols)
        j["underlying_symbols"] = *underlying_symbols;
    if (status)
        j["status"] = to_string(*status);
    if (expiration_date)
        j["expiration_date"] = *expiration_date;
    if (expiration_date_gte)
        j["expiration_date_gte"] = *expiration_date_gte;
    if (expiration_date_lte)
        j["expiration_date_lte"] = *expiration_date_lte;
    if (root_symbol)
        j["root_symbol"] = *root_symbol;
    if (type)
        j["type"] = to_string(*type);
    if (style)
        j["style"] = to_string(*style);
    if (strike_price_gte)
        j["strike_price_gte"] = *strike_price_gte;
    if (strike_price_lte)
        j["strike_price_lte"] = *strike_price_lte;
    if (limit)
        j["limit"] = *limit;
    if (page_token)
        j["page_token"] = *page_token;

    std::string json_string = j.dump(); // Serialize to JSON string
    return to_query_string(json_string);
}

StockBarsRequest::StockBarsRequest(
    std::vector<std::string> symbols,
    TimeFrame tframe,
    std::optional<std::string> start,
    std::optional<std::string> end,
    std::optional<int> limit) : symbols(std::move(symbols)), tframe(std::move(tframe)), start(std::move(start)), end(std::move(end)), limit(std::move(limit)) {};

std::string StockBarsRequest::to_fields() const
{
    nlohmann::json j;

    j["symbols"] = symbols;
    j["timeframe"] = tframe.frame;
    if (start.has_value())
        j["start"] = start;
    if (end.has_value())
        j["end"] = end;
    if (limit.has_value())
        j["limit"] = limit;

    return to_query_string(j.dump());
};

StockLatestBarRequest::StockLatestBarRequest(
    std::vector<std::string> symbols) : symbols(std::move(symbols)) {};

std::string StockLatestBarRequest::to_fields() const
{
    nlohmann::json j;
    j["symbols"] = symbols;
    return to_query_string(j.dump());
}

OptionBarRequest::OptionBarRequest(
    std::vector<std::string> symbols,
    TimeFrame tframe,
    std::optional<std::string> start,
    std::optional<std::string> end,
    std::optional<int> limit) : symbols(std::move(symbols)), tframe(std::move(tframe)), start(std::move(start)), end(std::move(end)), limit(std::move(limit)) {};

std::string OptionBarRequest::to_fields() const
{
    nlohmann::json j;

    j["symbols"] = symbols;
    j["timeframe"] = tframe.frame;
    if (start.has_value())
        j["start"] = start;
    if (end.has_value())
        j["end"] = end;
    if (limit.has_value())
        j["limit"] = limit;

    return to_query_string(j.dump());
};

OptionLatestBarRequest::OptionLatestBarRequest(
    std::vector<std::string> symbols) : symbols(std::move(symbols)) {};

std::string OptionLatestBarRequest::to_fields() const
{
    nlohmann::json j;
    j["symbols"] = symbols;
    return to_query_string(j.dump());
}

OptionChainRequest::OptionChainRequest(std::string underlying_symbol) : symbol(std::move(underlying_symbol)) {};
std::string OptionChainRequest::to_fields() const
{
    std::string output = "feed=indicative&limit=1000";
    return output;
};
;
