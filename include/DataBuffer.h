#pragma once
#include <string>
#include <queue>

class DataBuffer {
private:
    std::queue<std::string> buffer;
    const size_t maxSize; // Limite pour ne pas remplir toute la RAM

public:
    DataBuffer(size_t size) : maxSize(size) {}

    // Ajouter une donnée (Si full, on supprime la plus ancienne)
    void push(const std::string& data) {
        if (buffer.size() >= maxSize) {
            buffer.pop(); // On supprime le plus vieux si plein (FIFO)
        }
        buffer.push(data);
    }

    // Récupérer la donnée suivante (Retourne vide si vide)
    std::string pop() {
        if (buffer.empty()) return "";
        std::string data = buffer.front();
        buffer.pop();
        return data;
    }

    bool isEmpty() const { return buffer.empty(); }
    size_t size() const { return buffer.size(); }
};