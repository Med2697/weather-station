#pragma once
#include "IPublisher.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

class MqttPublisher : public IPublisher {
private:
    const char* mqtt_server;
    const int mqtt_port;
    WiFiClient espClient;
    PubSubClient client;
    const char* topic;

    void reconnect();

public:
    MqttPublisher(const char* server, int port, const char* topicName);
    void setup(); // Initialiser la connexion
    void publish(const std::string& data) override;
};