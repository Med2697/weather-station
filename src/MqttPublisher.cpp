#include "../include/MqttPublisher.h"
#include <Arduino.h>

MqttPublisher::MqttPublisher(const char* server, int port, const char* user, const char* pass, const char* topicName)
    : mqtt_server(server), mqtt_port(port), mqtt_user(user), mqtt_password(pass), topic(topicName), client(espClient) {
}

void MqttPublisher::setup() {
    espClient.setInsecure();
    client.setServer(mqtt_server, mqtt_port);
    reconnect();
}

void MqttPublisher::reconnect() {
    // Non-blocking reconnect logic
    int attempts = 0;
    while (!client.connected() && attempts < 5) {
        String clientId = "ESP32-" + String(WiFi.macAddress());
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
            return;
        }
        attempts++;
        delay(1000);
    }
}

void MqttPublisher::publish(const std::string& data) {
    if (!client.connected()) reconnect();
    
    if (client.connected()) {
        client.publish(topic, data.c_str());
    }
    
    client.loop();
}

bool MqttPublisher::isConnected() {
    return client.connected();
}