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
    
    IPublisher* networkPublisher; 

    std::string generateJsonReport();

public:
    WeatherStation(size_t bufferSize);
    void addSensor(ISensor* sensor);
    void addPublisher(IPublisher* publisher);
    void setNetworkPublisher(IPublisher* pub); // to verify if we are connected
    void readAllSensors();
    void publishReport();
};