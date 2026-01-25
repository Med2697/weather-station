#pragma once
#include "IPublisher.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <string>

class WifiPublisher : public IPublisher {
private:
    const char* ssid;
    const char* password;
    const char* serverUrl; // L'URL où on envoie les données (ex: Webhook)

public:
    WifiPublisher(const char* ssid, const char* password, const char* url);
    
    void connect();
    bool isConnected();
    void publish(const std::string& data) override;
};