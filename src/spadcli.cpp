#include <cstddef>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>

#include "spadcli.h"

//get synthetic signal
double randomNum(){
    static std::random_device random;
    static std::mt19937 gen(random());
    std::uniform_real_distribution<double> dis(-0.5, 0.5);
    return dis(gen);
}

void generateSyntheticSignal(const double& timeDelta, const double& time, std::vector<SensorPoint>& point){
    double pi = std::numbers::pi;
    size_t totalPoints = static_cast<size_t>(time/timeDelta);
    point.reserve(totalPoints);

    for(size_t i{0}; i < totalPoints; i++){
        double t{i*timeDelta};
        double raw{5.0 * std::sin( 2.0 * pi * 10.0 * t) 
                                        + 2.0 * std::cos(2 * pi * 50.0 * t) 
                                        + randomNum()
                    };
        if(t >= 2.500 && t <= 2.505){
            raw += 40.0;
        }

        point.push_back(SensorPoint{t, raw, 0.0});
    }
}

//apply moving average filter
void applyMovingAverageFilter(std::vector<SensorPoint>& input){
    size_t sizeofVector{input.size()};
    if(sizeofVector < 5){
        for(size_t i{0}; i< sizeofVector; i++){
            input[i].filtered_acceleration = input[i].raw_acceleration;
        }
        return;
    }
    input[0].filtered_acceleration = input[0].raw_acceleration;
    input[1].filtered_acceleration = input[1].raw_acceleration; //ilk iki değer filtrelenmez
    for (size_t i{2}; i < (sizeofVector - 2); i++){
        double filtering{};
        for (size_t j{0}; j<5; j++){
            filtering += input[i + j - 2].raw_acceleration;
        }
        input[i].filtered_acceleration = filtering / 5.0;
    }
    input[sizeofVector - 2].filtered_acceleration = input[sizeofVector - 2].raw_acceleration;
    input[sizeofVector - 1].filtered_acceleration = input[sizeofVector-1].raw_acceleration; //son iki değer filterlenmez
}

//calculate stats
SignalStats calculateStats(const std::vector<SensorPoint>& input){
    
    size_t vectorSize = input.size();
    if (vectorSize ==0) return{};

    double tempMean{};
    double tempSumfiltered{};
    for (size_t i{0}; i < vectorSize; i++){
        double val = input[i].filtered_acceleration;
        tempMean += val;
        tempSumfiltered +=(val * val);
    }

    double valueMean{tempMean/vectorSize};
    double valueRMSfiltered{std::sqrt(tempSumfiltered/vectorSize)};


    double maxValue{input[0].filtered_acceleration};
    double minValue{input[0].filtered_acceleration};
    for (size_t i{1}; i < vectorSize; i++){
        double val{input[i].filtered_acceleration};
        if(val > maxValue) maxValue = val;
        if(val < minValue) minValue = val;
    }
    
    return SignalStats{maxValue, minValue, valueMean, valueRMSfiltered};
}

//print signal stats
void printSignalStats(const SignalStats& stats){
    std::cout << "--- SIGNAL STATISTICS ---\n";
    std::cout << "Max Acc : " << stats.max_value << " g\n";
    std::cout << "Min Acc : " << stats.min_value << " g\n";
    std::cout << "Average : " << stats.mean << " g\n";
    std::cout << "RMS (Energy):" << stats.rms << " g\n";
}

//detect anomalies
void detectAnomalies(const std::vector<SensorPoint>& info){
    std::cout << "--- ANOMALY DETECTİON (Treshold > 15.0g) ---\n";
    constexpr std::string_view warn{"[WARN]"};
    size_t vecLength{info.size()};

    for(size_t i{0}; i< vecLength; i++){
        if(info[i].filtered_acceleration > 15.0){
            std::cout << warn << " " << "at" <<  info[i].timestamp
                << ". second. Anomaly Detected!\n"
                << "Value: " << info[i].filtered_acceleration
                << "g\n";
        }
    }
    std::cout << '\n';
}

//export to csv
void exportToCSV(const std::vector<SensorPoint>& sensor){

    std::ofstream accData("vibration_data.csv");

    if (accData.is_open()){
        accData << "timestamp,raw_acceleration,filtered_acceleration\n";
        
        size_t sizeData = sensor.size();
        for (size_t i {0}; i < sizeData; i++){
            accData << sensor[i].timestamp << ","
                    << sensor[i].raw_acceleration << ","
                    << sensor[i].filtered_acceleration << "\n";
        }

        accData.close();
        std::cout << "[SUCCESS] All data written in 'vibration_data.csv' succesfully." << '\n';
    }
    else{
        std::cerr << "[Error] File cannot created!!!" << '\n';
    }
}
