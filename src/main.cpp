#include <Arduino.h>
#include "WeatherStation.h"
#include "DHT22Sensor.h"
#include "SerialPublisher.h"
#include "WifiPublisher.h"
#include "MqttPublisher.h"


WeatherStation* station;
DHT22Sensor* sensorInside;
IPublisher* mqttPub;

void setup() {
    Serial.begin(115200);
    delay(1000); 

    // 1. Connection WiFi standard
    WiFi.begin("SSID", "PSWD");
    Serial.print("Connexion WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connecté!");

    // 2. Création des objets
    sensorInside = new DHT22Sensor(4, "Living Room");
    
    // 3. Initialisation du Publisher MQTT
    // Utilisation du broker public HiveMQ (Gratuit pour démo)
    mqttPub = new MqttPublisher("broker.hivemq.com", 1883, "weather/station/data");
    mqttPub->setup(); // Setup spécifique pour MQTT

    // 4. Configuration Station
    station = new WeatherStation();
    station->addSensor(sensorInside);
    
    // On garde Serial pour le Debug, mais on ajoute MQTT pour le "Real-time"
    station->addPublisher(new SerialPublisher());
    station->addPublisher(mqttPub);

    Serial.println("Système MQTT prêt.");
}

void loop() {
    station->readAllSensors();
    station->publishReport(); // Envoi JSON partout

    delay(5000); // 5 secondes pour laisser le temps au WiFi
}

