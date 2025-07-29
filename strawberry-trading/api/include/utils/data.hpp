#include <string>
#pragma once

enum class TimeFrameUnit
{
    Minute,
    Hour,
    Day,
    Week,
    Month
};

std::string timeframe2string(TimeFrameUnit timeframeunit);

class TimeFrame
{
public:
    TimeFrame(int amount, TimeFrameUnit tfunit);

    int amount;
    std::string unit;
    std::string frame;
};