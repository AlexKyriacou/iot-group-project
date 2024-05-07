#include "MotionDetector.h"

/**
 * @brief Constructs a new MotionDetector object.
 *
 * @param pirPin The pin number for the PIR sensor.
 */
MotionDetector::MotionDetector(int pirPin)
  : pirPin(pirPin), motionDetected(false) {}

/**
 * @brief Initializes the PIR sensor pin mode.
 */
void MotionDetector::setup() {
  pinMode(pirPin, INPUT);
}

/**
 * @brief Checks if motion is detected by the PIR sensor.
 *
 * @return true if motion is detected, false otherwise.
 */
bool MotionDetector::isMotionDetected() {
  bool pir = digitalRead(pirPin);
  if (pir) {
    motionDetected = true;  // Set the flag to true when motion is detected
  }
  return motionDetected;
}

/**
 * @brief Retrieves the motion detector data as a JsonDocument.
 *
 * @return A JsonDocument containing the motion detector data.
 */
JsonDocument MotionDetector::getJsonData() {
  JsonDocument doc;
  doc["deviceType"] = "motionDetector";
  doc["data"]["motion"] = isMotionDetected();
  motionDetected = false;  // Reset the flag after retrieving the JSON data
  return doc;
}