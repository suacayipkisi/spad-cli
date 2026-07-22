#include <random>
#include <cmath>
#include <numbers>
#include "coreStructures.h"
#include "genSyntheticSig.h"

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
        point[i].raw_acceleration = (5.0 * std::sin( 2.0 * pi * 10.0 * i * timeDelta) + 2.0 * std::cos(2 * pi * 50.0 * i *  timeDelta) + randomNum());
        if((i*timeDelta) >= 2.500 && (i*timeDelta) <= 2.505){
            point[i].raw_acceleration += 40.0;
        }
    }
}