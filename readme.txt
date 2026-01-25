ESP32 Weather Station - Enterprise Architecture
A robust, Object-Oriented C++ embedded system for data acquisition and telemetry.

🚀 Overview
This project demonstrates high-level software engineering practices applied to embedded hardware (ESP32). It decouples data acquisition from data transport, mimicking real-time trading system architectures.

🏗️ Architecture Highlights
OOP Design: Extensive use of Interfaces (ISensor, IPublisher) for modularity.
Dependency Injection: The WeatherStation logic is unaware of the hardware details (DHT22) or transport layers (Serial/WiFi).
Publisher/Subscriber Pattern: Single data source, multiple outputs (Serial Monitor & HTTP POST).
Performance: Uses StaticJsonDocument to avoid heap fragmentation (critical for 24/7 stability).
🛠️ Tech Stack
Hardware: ESP32-WROOM-32D, DHT22 Sensors.
Language: C++17 (Embedded).
Build System: PlatformIO (CMake-like for embedded).
Libraries: ArduinoJson, ESP32 WiFiClient.
📡 Data Flow
Sensors read physical values (Temp/Hum).
WeatherStation aggregates data.
Data is serialized to JSON (Standard Web Format).
JSON is pushed to all registered Publishers (Serial + HTTP Webhook).
🚀 Getting Started
Install PlatformIO extension in VS Code.
Configure WiFi credentials in src/main.cpp.
Upload to ESP32.