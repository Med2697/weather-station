#include "../include/DHT22Sensor.h"
#include <Arduino.h>

DHT22Sensor::DHT22Sensor(int pin, const char* sensorName) 
    : dht(pin, DHT22), name(sensorName), temperature(-40.0), humidity(0.0) {
    dht.begin();
    lastReportedValue = -100;
}

void DHT22Sensor::update() {
    float newTemp = dht.readTemperature();
    float newHum = dht.readHumidity();

   
    if (isnan(newTemp) || isnan(newHum)) {
        return; 
    }

    if (newTemp < -50.0 || newTemp > 60.0) {
        Serial.println("Outlier detecté : Température irréaliste. Rejet.");
        return;
    }

    temperature = newTemp;
    humidity = newHum;
}
float DHT22Sensor::getValue() const {
    return temperature;
}

const char* DHT22Sensor::getName() const {
    return name;
}

float DHT22Sensor::getHumidity() const{
    return humidity;
}

bool DHT22Sensor::hasChanged(float threshold) const {
    // The first lecture
    if (lastReportedValue == -100.0) {
        lastReportedValue = temperature; // Update
        return true;
    }
    
    float diff = std::abs(temperature - lastReportedValue);
    
    if (diff >= threshold) {
        lastReportedValue = temperature;
        return true;
    }
    return false;
}