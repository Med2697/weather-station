#pragma once
#include "Sensor.h"
#include "IPublisher.h"
#include <vector>

class WeatherStation {
private:
    std::vector<ISensor*> sensors;
    std::vector<IPublisher*> publishers; // Liste de tous les systèmes de sortie

    // Helper pour générer le JSON depuis les capteurs
    std::string generateJsonReport();

public:
    void addSensor(ISensor* sensor);
    void addPublisher(IPublisher* publisher); // Nouvelle méthode
    void readAllSensors();
    void publishReport();
};