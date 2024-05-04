#ifndef MotionDetector_h
#define MotionDetector_h

#include <ArduinoJson.h>

/**
 * @brief Class representing a motion detector sensor.
 */
class MotionDetector
{
public:
  /**
   * @brief Constructs a new MotionDetector object.
   *
   * @param pirPin The pin number for the PIR sensor.
   */
  MotionDetector(int pirPin);

  /**
   * @brief Initializes the PIR sensor pin mode.
   */
  void setup();

  /**
   * @brief Checks if motion is detected by the PIR sensor.
   *
   * @return true if motion is detected, false otherwise.
   */
  bool isMotionDetected();

  /**
   * @brief Retrieves the motion detector data as a JsonDocument.
   *
   * @return A JsonDocument containing the motion detector data.
   */
  JsonDocument getJsonData();

private:
  int pirPin; //!< The pin number for the PIR sensor.
};

#endif