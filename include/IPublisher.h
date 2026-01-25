#pragma once
#include <string>

// Interface Abstraite pour afficher/envoyer les données
class IPublisher {
public:
    virtual ~IPublisher() = default;
    
    // Méthode virtuelle pure pour publier un message (format String ou JSON)
    virtual void setup() =0;
    virtual void publish(const std::string& data) = 0;
};