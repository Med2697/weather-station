#include <Arduino.h>
#include "WeatherStation.h"
#include "DHT22Sensor.h"

WeatherStation* station;
DHT22Sensor* sensorInside;  // GPIO 4
DHT22Sensor* sensorOutside; // GPIO 5

void setup() {
    Serial.begin(115200);
    delay(1000); 
    Serial.println("Démarrage Station Météo ESP32...");

    // Initialisation des capteurs sur les pins 4 et 5
    sensorInside  = new DHT22Sensor(4, "Living Room");
    //sensorOutside = new DHT22Sensor(5, "Outside");

    station = new WeatherStation();
    station->addSensor(sensorInside);
    //station->addSensor(sensorOutside);

    Serial.println("Système Prêt.");
}

void loop() {
    station->readAllSensors();
    station->displayReport();

    delay(2000); // 2 secondes (DHT22 ne supporte pas des lectures plus rapides)
}