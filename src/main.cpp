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

    // WIFI
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connexion WiFi");
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nWiFi Connecté.");

    // MQTT
    sensorInside = new DHT22Sensor(4, "Living Room");
    mqttPub = new MqttPublisher(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, MQTT_TOPIC);
    mqttPub->setup();

    // STATION (Buffer de 20 messages max en RAM)
    station = new WeatherStation(20); 
    station->addSensor(sensorInside);
    station->addPublisher(new SerialPublisher());
    station->addPublisher(mqttPub);

    Serial.println("Système Prêt avec Buffer.");
}

void loop() {
    station->readAllSensors();
    station->publishReport();
    delay(2000);
}