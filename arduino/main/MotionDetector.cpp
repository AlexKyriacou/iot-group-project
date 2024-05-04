#include "MotionDetector.h"

/**
 * @brief Constructs a new MotionDetector object.
 *
 * @param pirPin The pin number for the PIR sensor.
 */
MotionDetector::MotionDetector(int pirPin) : pirPin(pirPin) {}

/**
 * @brief Initializes the PIR sensor pin mode.
 */
void MotionDetector::setup()
{
  pinMode(pirPin, INPUT);
}

/**
 * @brief Checks if motion is detected by the PIR sensor.
 *
 * @return true if motion is detected, false otherwise.
 */
bool MotionDetector::isMotionDetected()
{
  bool pir = digitalRead(pirPin);
  return pir;
}

/**
 * @brief Retrieves the motion detector data as a JsonDocument.
 *
 * @return A JsonDocument containing the motion detector data.
 */
JsonDocument MotionDetector::getJsonData()
{
  JsonDocument doc;
  doc["name"] = "motion_detector";
  doc["message"]["value"] = isMotionDetected();
  return doc;
}