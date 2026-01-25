#pragma once
#include "Sensor.h"
#include <DHT.h> // Inclusion de la librairie externe

// Pin et Type de capteur configurables à la construction
class DHT22Sensor : public ISensor {
private:
    DHT dht; // L'objet de la librairie
    const char* name;
    float temperature;
    float humidity;

public:
    // Constructeur : initialise la librairie sur le pin choisi
    DHT22Sensor(int pin, const char* sensorName);

    void update() override;
    float getValue() const override; // Retourne la Température
    const char* getName() const override;
    float getHumidity() const override; // Retourne l'hulmidité
};