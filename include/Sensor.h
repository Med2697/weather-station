#pragma once

class ISensor {
public:
    virtual ~ISensor() = default;
    virtual void update() = 0;       
    virtual float getValue() const = 0; 
    virtual const char* getName() const = 0; 
    
    // YOU MUST ADD THIS LINE HERE:
    // It provides a default implementation so we don't need dynamic_cast
    virtual float getHumidity() const { return -1.0; }
};