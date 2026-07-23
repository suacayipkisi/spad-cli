#pragma once

#include <vector>

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

double randomNum();
void generateSyntheticSignal(double& timeDelta, double& time, std::vector<SensorPoint>& point);

void applyMovingAverageFilter(std::vector<SensorPoint>& input);

SignalStats calculateStats(const std::vector<SensorPoint>& input);

void detectAnomalies(const std::vector<SensorPoint>& info);

void exportToCSV(const std::vector<SensorPoint>& sensor);
