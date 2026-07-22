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

//get synthetic signal
double randomNum();
void generateSyntheticSignal(double& timeDelta, double& time, std::vector<SensorPoint>& point);

//apply moving average filter
void applyMovingAverageFilter(std::vector<SensorPoint>& input);

//calculate stats
SignalStats calculateStats(const std::vector<SensorPoint>& input);

//detect anomalies
void detectAnomalies(const std::vector<SensorPoint>& info);

//export to csv
void exportToCSV(const std::vector<SensorPoint>& sensor);
