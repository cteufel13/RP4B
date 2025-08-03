#pragma once
#include <string>
#include <chrono>
#include <iostream>

std::chrono::system_clock::time_point from_unix_timestamp(int64_t unix_time);
std::chrono::system_clock::time_point from_tz_string(std::string tz_string);

class Date
{
public:
    Date();
    Date(int year, int month, int day);

    std::string to_string() const;
    static Date from_string(const std::string &str);
    static Date now();
    static Date max();
    Date operator+(std::chrono::days delta) const;
    Date operator-(std::chrono::days delta) const;
    bool operator==(const Date &other) const;

    friend bool operator<(const Date &lhs, const Date &rhs);
    friend bool operator>(const Date &lhs, const Date &rhs);
    friend bool operator<=(const Date &lhs, const Date &rhs);
    friend bool operator>=(const Date &lhs, const Date &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Date &obj);

    std::chrono::year_month_day date;
};
