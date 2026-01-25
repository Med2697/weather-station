#pragma once
#include "IPublisher.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string>

class MqttPublisher : public IPublisher {
private:
    const char* mqtt_server;
    const int mqtt_port;
    const char* mqtt_user;
    const char* mqtt_password;
    const char* topic;
    
    WiFiClientSecure espClient;
    PubSubClient client;

    void reconnect();

public:
    MqttPublisher(const char* server, int port, const char* user, const char* pass, const char* topicName);
    void setup(); 
    void publish(const std::string& data) override;
};