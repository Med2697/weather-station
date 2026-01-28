#include "../include/WifiPublisher.h"
#include <Arduino.h>

// We don't use this part in our main

WifiPublisher::WifiPublisher(const char* ssid, const char* password, const char* url)
    : ssid(ssid), password(password), serverUrl(url) {
}

void WifiPublisher::connect() {
    Serial.print("Connexion WiFi à ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connecté !");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nÉchec connexion WiFi.");
    }
}

bool WifiPublisher::isConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

void WifiPublisher::publish(const std::string& data) {
    if (WiFi.status() != WL_CONNECTED) {
        // If we lose the connexion, we try to connect
        connect();
        if (WiFi.status() != WL_CONNECTED) return; 
    }

    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Envoi de la requête POST
    int httpResponseCode = http.POST(data.c_str());

    if (httpResponseCode > 0) {

        Serial.println(httpResponseCode);
    }
    
    http.end();
}






