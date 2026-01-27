#pragma once
#include "Sensor.h"
#include "IPublisher.h"
#include "DataBuffer.h" 
#include <vector>

class WeatherStation {
private:
    std::vector<ISensor*> sensors;
    std::vector<IPublisher*> publishers;
    DataBuffer offlineBuffer; 
    
    // Optionnel: Un pointeur vers un Publisher pour vérifier s'il est connecté
    // (On pourrait passer ça dans le constructeur ou le setup)
    IPublisher* networkPublisher; 

    std::string generateJsonReport();

public:
    WeatherStation(size_t bufferSize);
    void addSensor(ISensor* sensor);
    void addPublisher(IPublisher* publisher);
    void setNetworkPublisher(IPublisher* pub); // Pour savoir si on est connecté ou pas
    void readAllSensors();
    void publishReport();
};