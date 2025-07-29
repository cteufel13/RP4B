#include <utils/data.hpp>
#include <string>

std::string timeframe2string(TimeFrameUnit timeframeunit)
{
    switch (timeframeunit)
    {
    case TimeFrameUnit::Minute:
        return "Min";
    case TimeFrameUnit::Day:
        return "Day";
    case TimeFrameUnit::Hour:
        return "Hour";
    case TimeFrameUnit::Month:
        return "Month";
    case TimeFrameUnit::Week:
        return "Week";
    }
}

TimeFrame::TimeFrame(int amount, TimeFrameUnit tfunit) : amount(amount), unit(timeframe2string(tfunit))
{
    frame = std::to_string(amount) + unit;
};