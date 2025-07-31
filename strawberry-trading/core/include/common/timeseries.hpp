#include <chrono>
#include <vector>

struct TimeSeriesPoint
{
    std::chrono::system_clock::time_point timestamp;
    std::unordered_map<std::string, double> values;
};

struct TimeSeries
{
    std::vector<TimeSeriesPoint> data;

    void addPoint(const TimeSeriesPoint &point)
    {
        data.push_back(point);
    }
};