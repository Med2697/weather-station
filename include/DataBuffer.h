#pragma once
#include <string>
#include <queue>

class DataBuffer {
private:
    std::queue<std::string> buffer;
    const size_t maxSize; // Limite pour ne pas remplir toute la RAM

public:
    DataBuffer(size_t size) : maxSize(size) {}

    // Add a data (If full, We delete the oldest one)
    void push(const std::string& data) {
        if (buffer.size() >= maxSize) {
            buffer.pop(); 
        }
        buffer.push(data);
    }

    // Return the next data (Return nothing if empty)
    std::string pop() {
        if (buffer.empty()) return "";
        std::string data = buffer.front();
        buffer.pop();
        return data;
    }

    bool isEmpty() const { return buffer.empty(); }
    size_t size() const { return buffer.size(); }
};