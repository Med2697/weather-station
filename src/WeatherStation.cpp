#include "../include/WeatherStation.h"
#include "../include/DHT22Sensor.h"
#include <Arduino.h>
#include <ArduinoJson.h> // Important pour générer le JSON

void WeatherStation::addSensor(ISensor* sensor) {
    sensors.push_back(sensor);
}

void WeatherStation::addPublisher(IPublisher* publisher) {
    publishers.push_back(publisher);
}

void WeatherStation::readAllSensors() {
    for (auto* sensor : sensors) {
        sensor->update();
    }
}

std::string WeatherStation::generateJsonReport() {
    // Utilisation de StaticJsonDocument pour économiser la RAM (Embedded Best Practice)
    StaticJsonDocument<256> doc;

    // Ajouter le timestamp
    doc["time"] = millis();

    // Création d'un tableau JSON pour les capteurs
    JsonArray sensorsArray = doc.createNestedArray("sensors");

    for (const auto* sensor : sensors) {
        JsonObject sensorObj = sensorsArray.createNestedObject();
        sensorObj["name"] = sensor->getName();
        sensorObj["temp"] = sensor->getValue();
        
        float hum = sensor->getHumidity();
        sensorObj["hum"] = hum;
    }

    // Sérialisation vers String
    std::string output;
    serializeJson(doc, output);
    return output;
}

void WeatherStation::publishReport() {
    std::string jsonData = generateJsonReport();

    // OPTIMISATION ICI :
    // On vérifie si au moins un capteur a changé significativement
    bool significantChange = false;
    for (const auto* sensor : sensors) {
        if (sensor->hasChanged(0.5)) { // Seuil de 0.5 degré
            significantChange = true;
            break; 
        }
    }

    // On publie SEULEMENT s'il y a eu un changement important
    if (significantChange) {
        for (auto* publisher : publishers) {
            publisher->publish(jsonData);
        }
    } else {
        // Debug optionnel
        Serial.println("Aucun changement significatif, envoi annulé (Bandwidth Saving)");
    }
}