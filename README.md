# 📡 IIoT Real-time Monitoring System: ESP32-S3 & Docker Stack

This project implements a complete Industrial Internet of Things (IIoT) pipeline, from edge data acquisition to professional visualization. It monitors environmental data (Temperature & Humidity) and proximity (Ultrasonic) using an ESP32-S3, delivering data via MQTT to a containerized stack.

## System Architecture
The system follows a 4-tier architecture:
1. **Edge Level:** ESP32-S3 + DHT22 (Temp/Hum) + HC-SR04 (Ultrasonic).
2. **Transport Level:** Mosquitto MQTT Broker.
3. **Orchestration Level:** Node-RED (Logic & Routing).
4. **Persistence & Visualization:** InfluxDB (TSDB) & Grafana Dashboards.

## Tech Stack
- **Hardware:** ESP32-S3 DevKit
- **Firmware:** C++ (Arduino Framework)
- **Containerization:** Docker & Docker Compose
- **Data Format:** JSON
- **Protocols:** MQTT, HTTP

## Quick Start
### Prerequisites
- Docker Desktop installed
- Arduino IDE with ESP32-S3 boards support

### 1. Spin up the Stack
Clone this repo and run:
```bash
docker-compose up -d

