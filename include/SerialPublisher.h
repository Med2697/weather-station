#pragma once
#include "IPublisher.h"
#include <string>

class SerialPublisher : public IPublisher {
public:
    void setup() override;
    void publish(const std::string& data) override;
    bool isConnected () override;
};
