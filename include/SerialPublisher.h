#pragma once
#include "IPublisher.h"
#include <string>

class SerialPublisher : public IPublisher {
public:
    void publish(const std::string& data) override;
};