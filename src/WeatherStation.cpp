#include "../include/WeatherStation.h"
#include "../include/DHT22Sensor.h"
#include "../include/MqttPublisher.h" // Pas indispensable mais bon à garder
#include <Arduino.h>
#include <ArduinoJson.h>

WeatherStation::WeatherStation(size_t bufferSize) : offlineBuffer(bufferSize) {}

void WeatherStation::addSensor(ISensor* sensor) { sensors.push_back(sensor); }

void WeatherStation::addPublisher(IPublisher* publisher) { 
    publishers.push_back(publisher); 
}

void WeatherStation::readAllSensors() {
    for (auto* sensor : sensors) { sensor->update(); }
}

std::string WeatherStation::generateJsonReport() {
    // ArduinoJson V7 Syntaxe
    JsonDocument doc;
    doc["time"] = millis();
    
    // V7 Syntaxe pour le tableau
    JsonArray sensorsArray = doc["sensors"].to<JsonArray>();

    for (const auto* sensor : sensors) {
        // V7 Syntaxe pour l'objet
        JsonObject s = sensorsArray.add<JsonObject>();
        s["name"] = sensor->getName();
        s["temp"] = sensor->getValue();
        float h = sensor->getHumidity();
        s["hum"] = h;
    }

    std::string output;
    serializeJson(doc, output);
    return output;
}

void WeatherStation::publishReport() {
    // 1. Vérification changements
    bool hasImportantChange = false;
    float threshold = 0.5;
    for (const auto* sensor : sensors) {
        if (sensor->hasChanged(threshold)) { hasImportantChange = true; break; }
    }

    if (hasImportantChange) {
        std::string currentData = generateJsonReport();

        // 2. Publication avec Gestion Buffer (Store & Forward)
        for (auto* publisher : publishers) {
            
            if (publisher->isConnected()) {
                // --- MODE ONLINE ---
                
                // 1. On essaye de vider le buffer (données passées)
                while (!offlineBuffer.isEmpty()) {
                    std::string oldData = offlineBuffer.pop();
                    Serial.print("[FLUSH] Anciennes données: ");
                    Serial.println(oldData.c_str());
                    publisher->publish(oldData);
                }
                
                // 2. On envoie la donnée actuelle
                Serial.print("[LIVE] Données actuelles: ");
                Serial.println(currentData.c_str());
                publisher->publish(currentData);
                
            } else {
                // --- MODE OFFLINE ---
                // Si le publisher est offline (ex: MQTT), on bufferise
                Serial.println("[BUFFER] Offline. Stockage...");
                offlineBuffer.push(currentData);
            }
        }
    }
}