#pragma once
#include "Sensor.h"
#include <vector>

// Note: Sur ESP32, utiliser std::vector et std::unique_ptr est acceptable
// car nous avons ~520KB de RAM.
class WeatherStation {
private:
    std::vector<ISensor*> sensors; // Pointeurs vers nos capteurs

public:
    void addSensor(ISensor* sensor);
    void readAllSensors();
    void displayReport();
};
