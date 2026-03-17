#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

// --- Config Hardware ---
#define DHTPIN 4
#define DHTTYPE DHT22
#define TRIG_PIN 16
#define ECHO_PIN 18

// --- Config Retea ---
const char ssid[] = "MERCUSYS_DAF7";
const char pass[] = "Tahfkc*74";
const char mqtt_broker[] = "192.168.1.101"; // IP-ul laptopului tau (ipconfig)
const int mqtt_port = 1883;
const char topic[] = "casa/senzori/camera1";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient net;
MqttClient mqttClient(net);

unsigned long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // MQTT
  mqttClient.setId("ESP32S3_Vancea_Main");
  if (!mqttClient.connect(mqtt_broker, mqtt_port)) {
    Serial.print("MQTT connection failed! Error = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("Connected to Broker!");
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return (duration == 0) ? -1 : (duration * 0.034 / 2);
}

void loop() {
  mqttClient.poll();

  unsigned long now = millis();
  if (now - lastMsg > 5000) { // Trimitem la 5 secunde
    lastMsg = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float d = getDistance();

    // Creare JSON robust
    StaticJsonDocument<200> doc;
    doc["temp"] = isnan(t) ? -99 : t;
    doc["hum"] = isnan(h) ? -99 : h;
    doc["dist"] = (d < 0) ? -1 : d;

    char buffer[256];
    serializeJson(doc, buffer);

    // Publicare
    mqttClient.beginMessage(topic);
    mqttClient.print(buffer);
    mqttClient.endMessage();

    Serial.print("Data sent: ");
    Serial.println(buffer);
  }
}
