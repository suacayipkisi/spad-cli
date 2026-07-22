#include <iostream>
#include <vector>

#include "src/spadcli.h"

int main(){
    double version{0.1};
    std::cout << "=== Vibration Signal Analysis Tool v" << version <<  " ===" << '\n';
    
    double duration{10.0}; //sec
    double dt{0.001}; //sec
    int dataPointNum{static_cast<int>(duration / dt)};
    
    std::vector<SensorPoint> allData{};
    generateSyntheticSignal(dt, duration, allData);
    
    std::cout << "[INFO] " << dataPointNum << " data point simulated"
        << " (Duration: " << duration << "s, "
        << "dt: " << dt << "s)." << '\n';

    applyMovingAverageFilter(allData);

    std::cout << "[INFO] " << "Dynamic enviroment filter applied (window size: 5)." << '\n';

    SignalStats allStats{calculateStats(allData)};

    std::cout << "--- SIGNAL STATISTICS ---\n";
    std::cout << "Max Acc : " << allStats.max_value << " g\n";
    std::cout << "Min Acc : " << allStats.min_value << " g\n";
    std::cout << "Average : " << allStats.mean << " g\n";
    std::cout << "RMS (Energy):" << allStats.rms << " g\n";

    detectAnomalies(allData);
    exportToCSV(allData);

    return 0;
}
