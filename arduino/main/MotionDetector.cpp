#include "MotionDetector.h"

MotionDetector::MotionDetector(int pirPin)
  : pirPin(pirPin), motionDetected(false) {}

void MotionDetector::setup() {
  pinMode(pirPin, INPUT);
}

bool MotionDetector::isDetected() {
  bool pir = digitalRead(pirPin);
  if (pir) {
    motionDetected = true;  // Set the flag to true when motion is detected
  }
  return motionDetected;
}

JsonDocument MotionDetector::getJsonData() {
  JsonDocument doc;
  doc["deviceType"] = "motionDetector";
  doc["data"]["motion"] = isDetected();
  motionDetected = false;  // Reset the flag after retrieving the JSON data
  return doc;
}