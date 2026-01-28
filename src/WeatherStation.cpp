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
    // ArduinoJson V7 Syntax
    JsonDocument doc;
    doc["time"] = millis();
    
    
    JsonArray sensorsArray = doc["sensors"].to<JsonArray>();

    for (const auto* sensor : sensors) {
        // V7 Syntaxe pour l'objet
        JsonObject s = sensorsArray.add<JsonObject>();
        s["name"] = sensor->getName();
        s["temp"] = sensor->getValue();
        s["hum"] = sensor->getHumidity();
    }

    std::string output;
    serializeJson(doc, output);
    return output;
}

void WeatherStation::publishReport() {
    
    bool hasImportantChange = false;
    float threshold = 0.5;
    for (const auto* sensor : sensors) {
        if (sensor->hasChanged(threshold)) { hasImportantChange = true; break; }
    }

    if (hasImportantChange) {
        std::string currentData = generateJsonReport();

        
        for (auto* publisher : publishers) {
            
            if (publisher->isConnected()) {
                // --- MODE ONLINE ---
                
                
                while (!offlineBuffer.isEmpty()) {
                    std::string oldData = offlineBuffer.pop();
                    Serial.print("[FLUSH] old datas: ");
                    Serial.println(oldData.c_str());
                    publisher->publish(oldData);
                }
                
                
                Serial.print("[LIVE] actual datas: ");
                Serial.println(currentData.c_str());
                publisher->publish(currentData);
                
            } else {
                // --- MODE OFFLINE ---
                
                Serial.println("[BUFFER] Offline. Stockage...");
                offlineBuffer.push(currentData);
            }
        }
    }
}