#include <vector>
#include <cmath>
#include "coreStructures.h"


SignalStats calculateStats(const std::vector<SensorPoint>& input){
    
    int vectorSize{static_cast<int>(input.size())};

    double tempMean{};
    double tempSumfiltered{};
    for (int i{0}; i < vectorSize; i++){
        tempMean += input[i].filtered_acceleration;
        tempSumfiltered += std::pow(input[i].filtered_acceleration, 2);
    }
    double valueMean{tempMean/vectorSize};
    double valueRMSfiltered{static_cast<double>(std::sqrtl(tempSumfiltered/vectorSize))};


    double maxValue{input[0].filtered_acceleration};
    double minValue{input[0].filtered_acceleration};
    for (int i{1}; i < vectorSize; i++){
        if(input[i].filtered_acceleration > maxValue){
            maxValue = input[i].filtered_acceleration;
        }
        if(input[i].filtered_acceleration < minValue){
            minValue = input[i].filtered_acceleration;
        }
    }
    
    SignalStats stat{maxValue, minValue, valueMean, valueRMSfiltered};
    return stat;
}