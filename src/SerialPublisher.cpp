#include "../include/SerialPublisher.h"
#include <Arduino.h>

void SerialPublisher::setup() {
    // It is already ready
}

void SerialPublisher::publish(const std::string& data) {
    Serial.println(data.c_str());
}

bool SerialPublisher::isConnected() {
    return true;
}