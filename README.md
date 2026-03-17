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
```

### 2 Flash the Firmware
Open `firmware/main.ino` in Arduino IDE and configure your local environment:

* **Network Setup:**
    ```cpp
    const char ssid[] = "YOUR_WIFI_SSID";
    const char pass[] = "YOUR_WIFI_PASSWORD";
    const char mqtt_broker[] = "YOUR_LAPTOP_IP"; // Use 'ipconfig' or 'ifconfig'
    ```
* **Board Settings:**
    * Select **ESP32S3 Dev Module**.
    * **USB CDC On Boot:** `Enabled` (Crucial for Serial Monitor).

### 3 Data Flow Validation
* **Serial Monitor:** Set to `115200` baud. Look for `WiFi Connected` and `MQTT Published`.
* **Node-RED:** Visit `http://localhost:1880`. Verify the MQTT-in node shows "connected".
* **InfluxDB:** Access `http://localhost:8086`. Check if the `IoT_Bucket` is populating.

---

## 4 Visualizations
* **InfluxDB:** Access `http://localhost:8086`. Check if the `IoT_Bucket` is populating.
* **Grafana:** Access `[http://localhost:8086](http://localhost:3000)` (Default: `admin/admin`).
