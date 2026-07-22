#include <iostream>
#include <string_view>
#include <vector>

#include "detectAnomalies.h"
#include "coreStructures.h"


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