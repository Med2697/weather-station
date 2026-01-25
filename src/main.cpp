#include <Arduino.h>
#include "WeatherStation.h"
#include "DHT22Sensor.h"
#include "SerialPublisher.h"
#include "MqttPublisher.h"
#include "secrets.h"


WeatherStation* station;
DHT22Sensor* sensorInside;
IPublisher* mqttPub; 

void setup() {
    Serial.begin(115200);
    delay(1000); 

    // --- 1. WIFI ---
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connexion WiFi");
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nWiFi Connecté.");

    // --- 2. CONFIGURATION HIVEMQ CLOUD ---
    // Remplace ces lignes par TES infos
    const char* mqttServer = MQTT_SERVER;
    int mqttPort = MQTT_PORT; 
    const char* mqttUser = MQTT_USER;
    const char* mqttPass = MQTT_PASSWORD;
    const char* mqttTopic = MQTT_TOPIC;

    sensorInside = new DHT22Sensor(4, "Living Room");
    
    mqttPub = new MqttPublisher(mqttServer, mqttPort, mqttUser, mqttPass, mqttTopic);
    mqttPub->setup();

    station = new WeatherStation();
    station->addSensor(sensorInside);
    station->addPublisher(new SerialPublisher());
    station->addPublisher(mqttPub);

    Serial.println("Système Prêt (Smart Publishing ON).");
}

void loop() {
    station->readAllSensors();
    station->publishReport();

    delay(2000); // Vérifie toutes les 2 secondes
}