#pragma once

class ISensor {
public:
    virtual ~ISensor() = default;
    virtual void update() = 0;       
    virtual float getValue() const = 0;
    virtual float getHumidity() const =0; 
    virtual const char* getName() const = 0; 
    // verify if the value has changed significantly
    virtual bool hasChanged(float threshold) const = 0;
};