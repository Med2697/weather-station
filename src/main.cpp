#include <Arduino.h>
#include "WeatherStation.h"
#include "DHT22Sensor.h"
#include "SerialPublisher.h"
#include "WifiPublisher.h"

WeatherStation* station;
DHT22Sensor* sensorInside;

void setup() {
    Serial.begin(115200);
    delay(1000); 

    // --- 1. Création des Capteurs ---
    sensorInside = new DHT22Sensor(4, "Living Room");

    // --- 2. Création des Publishers (Sorties) ---
    IPublisher* serialPub = new SerialPublisher();
    
    // REMPLACE PAR TON WIFI ET TON WEBHOOK (ou URL serveur local)
    IPublisher* wifiPub = new WifiPublisher("SSID", "MDP", "https://webhook.site/Id");

    // --- 3. Configuration de la Station ---
    station = new WeatherStation();
    station->addSensor(sensorInside);
    
    // Ajout des deux sorties : La station enverra les données AUSSI au Serial, ET au Wifi
    station->addPublisher(serialPub);
    station->addPublisher(wifiPub);

    Serial.println("Système Prêt avec Publishers (Serial + Wifi).");
}

void loop() {
    station->readAllSensors();
    station->publishReport(); // Envoi JSON partout

    delay(5000); // 5 secondes pour laisser le temps au WiFi
}