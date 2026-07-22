#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include "coreStructures.h"
#include "exportToCSV.h"

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