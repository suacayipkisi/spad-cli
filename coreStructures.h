#pragma once

enum class FilterType{
    None,
    MovingAverage,
};

struct SensorPoint{
    double timestamp{};//sec
    double raw_acceleration{}; //g force
    double filtered_acceleration{};
};

struct SignalStats{
    double max_value{};
    double min_value{};
    double mean{}; //average
    double rms{};  //root mean square
};