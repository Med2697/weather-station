#include "../include/WeatherStation.h"
#include "../include/DHT22Sensor.h" 
#include <Arduino.h>

void WeatherStation::addSensor(ISensor* sensor) {
    sensors.push_back(sensor);
}

void WeatherStation::readAllSensors() {
    for (auto* sensor : sensors) {
        sensor->update();
    }
}

void WeatherStation::displayReport() {
    Serial.println("=== Weather Report ===");
    for (const auto* sensor : sensors) {
        Serial.print(sensor->getName());
        Serial.print(": Temp ");
        Serial.print(sensor->getValue());
        Serial.print(" C | ");

        // On utilise maintenant la méthode de l'interface (getHumidity).
        // Si le capteur ne gère pas l'humidité, ISensor renvoie -1.0 par défaut.
        float hum = sensor->getHumidity();
        
        if (hum != -1.0) {
            Serial.print("Hum: ");
            Serial.print(hum);
            Serial.println(" %");
        } else {
            Serial.println(); // Saut de ligne simple
        }
    }
    Serial.println("======================");
}