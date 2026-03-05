#include <Arduino.h>

struct SensorData {
  float temperature;
  float humidity;
  int light;
};

// Global sensor structure (allocated once - no heap usage)
SensorData sensor;

// Function now fills an existing struct (no dynamic memory)
void readSensors(SensorData &data) {
  data.temperature = random(200, 300) / 10.0;  // 20.0 - 30.0 °C
  data.humidity = random(300, 600) / 10.0;     // 30.0 - 60.0 %
  data.light = random(0, 1024);                // ADC range
}

void setup() {
  Serial.begin(115200);
  delay(1000); // small startup delay
  Serial.println("ESP32 Memory Leak Prevention Demo");
}

void loop() {

  // Fill struct without allocating memory
  readSensors(sensor);

  // Print system memory
  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());

  // Print sensor values
  Serial.print(" | Temp: ");
  Serial.print(sensor.temperature);
  Serial.print(" °C");

  Serial.print(" | Hum: ");
  Serial.print(sensor.humidity);
  Serial.print(" %");

  Serial.print(" | Light: ");
  Serial.println(sensor.light);

  delay(1000);
}