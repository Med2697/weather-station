#include "../include/WifiPublisher.h"
#include <Arduino.h>

WifiPublisher::WifiPublisher(const char* ssid, const char* password, const char* url)
    : ssid(ssid), password(password), serverUrl(url) {
}

void WifiPublisher::connect() {
    Serial.print("Connexion WiFi à ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);

    // On attend la connexion (timeout 10 sec pour éviter de bloquer trop)
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
        // Si on perd la connexion, on essaie de se reconnecter
        connect();
        if (WiFi.status() != WL_CONNECTED) return; // Toujours pas connecté, on abandonne
    }

    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Envoi de la requête POST
    int httpResponseCode = http.POST(data.c_str());

    // On vérifie la réponse sans afficher trop de logs pour ne pas polluer
    if (httpResponseCode > 0) {
        // String response = http.getString(); // Debug si besoin
        // Serial.println(httpResponseCode);
    }
    
    http.end();
}