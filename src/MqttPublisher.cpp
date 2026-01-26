#include "../include/MqttPublisher.h"
#include <Arduino.h>

MqttPublisher::MqttPublisher(const char* server, int port, const char* user, const char* pass, const char* topicName): mqtt_server(server), mqtt_port(port), mqtt_user(user), mqtt_password(pass), topic(topicName), client(espClient) {
}

void MqttPublisher::setup() {
    espClient.setInsecure();
    client.setServer(mqtt_server, mqtt_port);
    reconnect(); // Tentative initiale (bloquante OK au démarrage)
}

void MqttPublisher::reconnect() {
    // OPTIMISATION : On n'essaie pas indéfiniment.
    // On limite à 5 tentatives pour éviter le freeze.
    int attempts = 0;
    while (!client.connected() && attempts < 5) {
        Serial.print("Tentative MQTT...");
        String clientId = "ESP32-" + String(WiFi.macAddress());
        
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
            Serial.println("Connecté !");
            return;
        }
        Serial.print("Echec ");
        Serial.println(attempts);
        attempts++;
        delay(1000); // Attente courte
    }
    
    if (!client.connected()) {
        Serial.println("Timeout connexion MQTT. On continue le système (Non-Blocking).");
    }
}

void MqttPublisher::publish(const std::string& data) {
    // Si déconnecté, on tente une reconnexion RAPIDE (sans bloquer)
    if (!client.connected()) {
        reconnect(); // Cette version quitte si ça échoue après 5 sec
    }
    
    // On essaie de publier seulement si connecté
    if (client.connected()) {
        client.publish(topic, data.c_str());
    }
    
    client.loop();
}