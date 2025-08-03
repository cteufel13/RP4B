#include <chrono>
#include <utils/timeseries_utils.hpp>
#include <sstream>
#include <iomanip>
#include "date/date.h"

std::chrono::system_clock::time_point from_unix_timestamp(int64_t unix_time)
{
    return std::chrono::system_clock::time_point{std::chrono::seconds{unix_time}};
}
std::chrono::system_clock::time_point from_tz_string(std::string tz_string)
{
    std::tm tm = {};
    std::istringstream ss(tz_string);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ"); // assumes UTC 'Z'

    std::time_t time = timegm(&tm); // UTC-safe version of mktime (non-standard but works on Unix)
    return std::chrono::system_clock::from_time_t(time);
};

Date::Date() : date(std::chrono::year{1970} / 1 / 1) {}

Date::Date(int year, int month, int day)
    : date(std::chrono::year{year} / std::chrono::month{static_cast<unsigned>(month)} / std::chrono::day{static_cast<unsigned>(day)}) {}

std::string Date::to_string() const
{
    std::ostringstream oss;
    oss << int(date.year()) << "-"
        << std::setw(2) << std::setfill('0') << unsigned(date.month()) << "-"
        << std::setw(2) << std::setfill('0') << unsigned(date.day());
    return oss.str();
}

Date Date::from_string(const std::string &str)
{
    if (str.find('-') != std::string::npos)
    {
        int y, m, d;
        sscanf(str.c_str(), "%d-%d-%d", &y, &m, &d);
        return Date(y, m, d);
    }
    else
    {
        int y = std::stoi(str.substr(0, 4));
        int m = std::stoi(str.substr(4, 2));
        int d = std::stoi(str.substr(6, 2));
        return Date(y, m, d);
    }
}

Date Date::now()
{
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    auto ymd = std::chrono::year_month_day{today};
    return Date(int(ymd.year()), unsigned(ymd.month()), unsigned(ymd.day()));
}

Date Date::max()
{
    return Date(9999, 12, 31);
};

Date Date::operator+(std::chrono::days delta) const
{
    auto sys_days = std::chrono::sys_days{date} + delta;
    auto ymd = std::chrono::year_month_day{sys_days};
    return Date(
        static_cast<int>(ymd.year()),
        static_cast<unsigned>(ymd.month()),
        static_cast<unsigned>(ymd.day()));
}

Date Date::operator-(std::chrono::days delta) const
{
    auto sys_days = std::chrono::sys_days{date} - delta;
    auto ymd = std::chrono::year_month_day{sys_days};
    return Date(
        static_cast<int>(ymd.year()),
        static_cast<unsigned>(ymd.month()),
        static_cast<unsigned>(ymd.day()));
}

bool Date::operator==(const Date &other) const
{
    return date == other.date;
}

bool operator<(const Date &lhs, const Date &rhs)
{
    return lhs.date < rhs.date;
}

bool operator>(const Date &lhs, const Date &rhs)
{
    return lhs.date > rhs.date;
}

bool operator<=(const Date &lhs, const Date &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const Date &lhs, const Date &rhs)
{
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const Date &obj)
{
    os << "Date(" << obj.date << ")";
    return os;
}