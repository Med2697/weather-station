ESP32 Weather Station - Enterprise Architecture
A robust, Object-Oriented C++ embedded system for data acquisition and telemetry, designed for high availability and data integrity.

🚀 Overview
This project demonstrates high-level software engineering practices applied to embedded hardware (ESP32). It decouples data acquisition from data transport, mimicking real-time trading system architectures (Pub/Sub patterns).

🏗️ Architecture Highlights
OOP Design: Extensive use of Interfaces (ISensor, IPublisher) for modularity and extensibility.
Decoupling: The WeatherStation logic is unaware of hardware details (DHT22) or transport layers (MQTT/Serial). This allows seamless hardware or cloud migration.
Publisher/Subscriber Pattern: Single data source, multiple outputs (Serial Monitor + MQTT Broker).
Performance: Uses StaticJsonDocument to avoid heap fragmentation (critical for 24/7 embedded stability).
Reliability:
Store & Forward: Implements an in-memory RAM buffer (DataBuffer) to queue data during network outages. Data is flushed automatically upon reconnection.
Sanitizing: Filters out sensor noise/outliers before transmission.
Non-Blocking I/O: Handles network timeouts gracefully without freezing the system.
🛠️ Tech Stack
Hardware: ESP32-WROOM-32D, DHT22 Sensors.
Language: C++17 (Embedded).
Build System: PlatformIO (CMake-like for embedded).
Libraries: ArduinoJson, PubSubClient, WiFiClientSecure (TLS/SSL).
📡 Data Flow
Sensors read physical values (Temp/Hum).
DataBuffer holds data if network is offline (Resilience).
WeatherStation aggregates data and sanitizes inputs.
Serialization: Data is serialized to JSON (Standard Web Format).
Transport: JSON is pushed to all registered Publishers (Serial & Secure MQTT HiveMQ).
🚀 Getting Started
PlatformIO: Install PlatformIO extension in VS Code.
Configuration:
Copy include/secrets.h.example to include/secrets.h.
Fill in your WiFi credentials and HiveMQ Cloud details in secrets.h.
Build & Upload: Upload to ESP32.
Visualization: Connect to HiveMQ Cloud Dashboard to see real-time telemetry.