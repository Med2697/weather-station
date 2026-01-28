#pragma once
#include "Sensor.h"
#include <DHT.h>

class DHT22Sensor : public ISensor {
private:
    DHT dht; // The library object
    const char* name;
    float temperature;
    float humidity;
    mutable float lastReportedValue;

public:
    DHT22Sensor(int pin, const char* sensorName);

    void update() override;
    float getValue() const override; // return the temperature
    const char* getName() const override;
    float getHumidity() const override; // return the humidity
    bool hasChanged (float threeshold) const override;
};