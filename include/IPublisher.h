#pragma once
#include <string>

// Abstract interface for displaying/sending data
class IPublisher {
public:
    virtual ~IPublisher() = default;
    
    virtual void setup() =0;
    virtual void publish(const std::string& data) = 0;
    virtual bool isConnected() = 0;
};