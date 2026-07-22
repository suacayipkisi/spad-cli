# SPAD_CLI (Signal Processing and Anomaly Detection)

This tool is designed to simulate, filter and analyze vibration sensor signals. (c++20 standarts)

## Features
- **Signal Generation:** Simulates multi-frequency sinusoidal vibration data with Gaussian noise and shock anomalies.
- **Moving Average Filter:** Smooths raw acceleration data using a dynamic window.
- **Statistical Analysis:** Calculates Min, Max, Mean, and RMS (Energy) values.
- **Anomaly Detection:** Real-time threshold monitoring (>15.0g) with timestamp logging.
- **Data Export:** Exports structured results to CSV for analysis.

## Build and Run

```bash
mkdir build && cd build
cmake ..
make
./spadcli
```

#### This code is a test-education code. I do not recommend to use in a big project directly.