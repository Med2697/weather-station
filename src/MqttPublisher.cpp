#include "../include/MqttPublisher.h"
#include <Arduino.h>

MqttPublisher::MqttPublisher(const char* server, int port, const char* user, const char* pass, const char* topicName)
    : mqtt_server(server), mqtt_port(port), mqtt_user(user), mqtt_password(pass), topic(topicName), client(espClient) {
}

void MqttPublisher::setup() {
    // SSL sans vérification de certificat (Pour démo HiveMQ Cloud)
    espClient.setInsecure();
    
    client.setServer(mqtt_server, mqtt_port);
    reconnect();
}

void MqttPublisher::reconnect() {
    while (!client.connected()) {
        Serial.print("Connexion MQTT Cloud...");
        String clientId = "ESP32-" + String(WiFi.macAddress());
        
        // Connexion avec User/Pass
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
            Serial.println("Connecté !");
        } else {
            Serial.print("Erreur : ");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void MqttPublisher::publish(const std::string& data) {
    if (!client.connected()) reconnect();
    client.publish(topic, data.c_str());
    client.loop();
}