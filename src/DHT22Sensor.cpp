#include "../include/DHT22Sensor.h"
#include <Arduino.h>

DHT22Sensor::DHT22Sensor(int pin, const char* sensorName) 
    : dht(pin, DHT22), name(sensorName), temperature(-99.0), humidity(0.0) {
    dht.begin();
}

void DHT22Sensor::update() {
    float newTemp = dht.readTemperature();
    float newHum = dht.readHumidity();

    if (isnan(newTemp) || isnan(newHum)) {
        Serial.print("Erreur lecture sur "); 
        Serial.println(name);
    } else {
        temperature = newTemp;
        humidity = newHum;
    }
}

float DHT22Sensor::getValue() const {
    return temperature;
}

const char* DHT22Sensor::getName() const {
    return name;
}

float DHT22Sensor::getHumidity() const {
    return humidity;
}