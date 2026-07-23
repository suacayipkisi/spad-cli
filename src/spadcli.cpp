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
    double randomDouble = dis(gen);
    return randomDouble;
}

void generateSyntheticSignal(double& timeDelta, double& time, std::vector<SensorPoint>& point){
    double pi = std::numbers::pi;
    for(int i{0}; i < (time/timeDelta); i++){
        point.push_back({});
        point[i].timestamp = (i*timeDelta);
        point[i].raw_acceleration = (5.0 * std::sin( 2.0 * pi * 10.0 * i * timeDelta) 
                                        + 2.0 * std::cos(2 * pi * 50.0 * i *  timeDelta) 
                                        + randomNum());
        if((i*timeDelta) >= 2.500 && (i*timeDelta) <= 2.505){
            point[i].raw_acceleration += 40.0;
        }
    }
}

//apply moving average filter
void applyMovingAverageFilter(std::vector<SensorPoint>& input){
    int sizeofVector{static_cast<int>(input.size())};
    std::vector<double> filtered;
    filtered.push_back(input[0].raw_acceleration);
    filtered.push_back(input[1].raw_acceleration); //ilk iki değer filtrelenmez
    for (int i{2}; i < (sizeofVector - 2); i++){
        double filtering{};
        for (int j{0}; j<5; j++){
            filtering += input[i + j - 2].raw_acceleration;
        }
        filtering /= 5;
        filtered.push_back(filtering);
    }
    filtered.push_back(input[sizeofVector-2].raw_acceleration);
    filtered.push_back(input[sizeofVector-1].raw_acceleration); //son iki değer filterlenmez

    for(int i{0}; i<sizeofVector; i++){
        input[i].filtered_acceleration = filtered[i];
    }
}

//calculate stats
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

//print signal stats
void printSignalStats(SignalStats& stats){
    std::cout << "--- SIGNAL STATISTICS ---\n";
    std::cout << "Max Acc : " << stats.max_value << " g\n";
    std::cout << "Min Acc : " << stats.min_value << " g\n";
    std::cout << "Average : " << stats.mean << " g\n";
    std::cout << "RMS (Energy):" << stats.rms << " g\n";
}

//detect anomalies
void detectAnomalies(const std::vector<SensorPoint>& info){
    std::cout << "--- ANOMALY DETECTİON (Treshold > 15.0g) ---\n";
    std::string_view warn{"[WARN]"};
    int vecLength{static_cast<int>(info.size())};
    for(int i{0}; i< vecLength; i++){
        if(info[i].filtered_acceleration > 15.0){
            std::cout << warn << " " << "at" <<  info[i].timestamp
                << ". second. Anomaly Detected!\n";
            std::cout << "Value: " << info[i].filtered_acceleration
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
