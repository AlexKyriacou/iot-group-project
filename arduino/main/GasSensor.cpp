#include "GasSensor.h"
int gasThreshold = 350;

GasSensor::GasSensor(int gasPin)
  : gasPin(gasPin), gasDetected(false) {}

void GasSensor::setup() {
  pinMode(gasPin, INPUT);
}

float GasSensor::value() {
  float gas = analogRead(gasPin);
  if (gas > gasThreshold) {
    gasDetected = true;  // Set the flag to true when motion is detected
  }

  return gas;
}

bool GasSensor::isDetected() {
  return gasDetected;
}

JsonDocument GasSensor::getJsonData() {
  JsonDocument doc;
  doc["deviceType"] = "gasSensor";
  doc["data"]["gas"] = isDetected();
  doc["data"]["gasLevel"] = value();
  gasDetected = false;  // Reset the flag after retrieving the JSON data
  return doc;
}