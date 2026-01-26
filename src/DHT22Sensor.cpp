#include "../include/DHT22Sensor.h"
#include <Arduino.h>

DHT22Sensor::DHT22Sensor(int pin, const char* sensorName) 
    : dht(pin, DHT22), name(sensorName), temperature(-99.0), humidity(0.0) {
    dht.begin();
}

void DHT22Sensor::update() {
    float newTemp = dht.readTemperature();
    float newHum = dht.readHumidity();

    // 1. Vérification de la connexion capteur (Erreur de lecture)
    if (isnan(newTemp) || isnan(newHum)) {
        return; // On ignore tout
    }

    // 2. Vérification de l'intégrité physique (Sanitizing)
    // Une température entre -50 et 60 est raisonnable pour la météo
    if (newTemp < -50.0 || newTemp > 60.0) {
        Serial.println("Outlier detecté : Température irréaliste. Rejet.");
        return;
    }

    // Si on arrive là, c'est une donnée propre
    temperature = newTemp;
    humidity = newHum;
}
float DHT22Sensor::getValue() const {
    return temperature;
}

const char* DHT22Sensor::getName() const {
    return name;
}

float DHT22Sensor::getHumidity() const {
    return humidity;
}

bool DHT22Sensor::hasChanged(float threshold) const {
    // Si c'est la première lecture, on considère que ça a changé
    if (lastReportedValue == -100.0) {
        lastReportedValue = temperature; // Mise à jour (très sale mais ça marche pour la démo)
        return true;
    }
    
    // Calculer la différence absolue
    float diff = std::abs(temperature - lastReportedValue);
    
    if (diff >= threshold) {
        // IMPORTANT : Il faut mettre à jour la valeur de référence !
        // Comme la méthode est const, on ne peut pas modifier lastReportedValue ici facilement
        // sans utiliser le mot clé mutable.
        // Pour l'instant, on retourne juste true. (On corrigera la logique de "latch" si tu veux que ça s'arrête)
        
        // Note : Pour faire propre et autoriser la modification dans une fonction const,
        // ajoute 'mutable' devant 'float lastReportedValue' dans le .h
        lastReportedValue = temperature;
        return true;
    }
    return false;
}


