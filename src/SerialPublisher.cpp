#include "../include/SerialPublisher.h"
#include <Arduino.h>

void SerialPublisher::publish(const std::string& data) {
    // Simplement envoyer les données au port série
    Serial.println(data.c_str());
}