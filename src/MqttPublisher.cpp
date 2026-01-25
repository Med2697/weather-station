#include "../include/MqttPublisher.h"
#include <Arduino.h>

MqttPublisher::MqttPublisher(const char* server, int port, const char* topicName)
    : mqtt_server(server), mqtt_port(port), topic(topicName), client(espClient) {
}

void MqttPublisher::setup() {
    client.setServer(mqtt_server, mqtt_port);
    reconnect();
}

void MqttPublisher::reconnect() {
    // Boucle tant que non connecté
    while (!client.connected()) {
        Serial.print("Tentative de connexion MQTT...");
        // ID Client unique (généré depuis l'adresse MAC)
        String clientId = "ESP32Client-" + String(WiFi.macAddress());
        
        if (client.connect(clientId.c_str())) {
            Serial.println("connecté");
        } else {
            Serial.print("échec, rc=");
            Serial.print(client.state());
            Serial.println(" réessai dans 5s");
            delay(5000);
        }
    }
}

void MqttPublisher::publish(const std::string& data) {
    // S'assurer qu'on est connecté
    if (!client.connected()) {
        reconnect();
    }
    // Publier les données JSON sur le topic
    client.publish(topic, data.c_str());
    
    // Boucle interne du client MQTT (nécessaire pour gérer les keep-alives)
    // Note : Dans une architecture pro, on ferait ça dans le main loop via un callback,
    // mais ici on le met ici pour simplifier la démo.
    client.loop(); 
}