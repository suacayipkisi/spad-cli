#include <vector>
#include "coreStructures.h"

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