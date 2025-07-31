#include <chrono>

std::chrono::system_clock::time_point from_unix_timestamp(int64_t unix_time)
{
    return std::chrono::system_clock::time_point{std::chrono::seconds{unix_time}};
}
