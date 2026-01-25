#include "../include/SerialPublisher.h"
#include <Arduino.h>

void SerialPublisher::setup() {
    // Rien à faire pour le port série, il est déjà prêt.
}

void SerialPublisher::publish(const std::string& data) {
    // Simplement envoyer les données au port série
    Serial.println(data.c_str());
}
