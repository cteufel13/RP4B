#pragma once
#include <string>
#include <chrono>

std::chrono::system_clock::time_point from_unix_timestamp(int64_t unix_time);

class Date
{
public:
    Date();
    Date(int year, int month, int day);

    std::string to_string() const;
    static Date from_string(const std::string &str);
    static Date now();
    Date operator+(std::chrono::days delta) const;

    std::chrono::year_month_day date;
};
