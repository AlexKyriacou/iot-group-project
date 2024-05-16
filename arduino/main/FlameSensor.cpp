#include "FlameSensor.h"
int flameThreshold = 800;

FlameSensor::FlameSensor(int flamePin)
  : flamePin(flamePin), flameDetected(false) {}

void FlameSensor::setup() {
  pinMode(flamePin, INPUT);
}

float FlameSensor::value() {
  float flame = analogRead(flamePin);
  if (flame < flameThreshold) {
    flameDetected = true;  // Set the flag to true when motion is detected
  }
  return flame;
}

bool FlameSensor::isDetected() {
  return flameDetected;
}

JsonDocument FlameSensor::getJsonData() {
  JsonDocument doc;
  doc["data"]["flame"] = value();
  flameDetected = false;  // Reset the flag after retrieving the JSON data
  return doc;
}

String FlameSensor::getType() {
  return "flameSensor";
}