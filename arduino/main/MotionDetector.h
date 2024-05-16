#ifndef MotionDetector_h
#define MotionDetector_h

#include "Sensor.h"

class MotionDetector : public Sensor {
public:
  MotionDetector(int pirPin);
  void setup() override;
  bool isDetected() override;
  JsonDocument getJsonData() override;
  String getType() override;

private:
  int pirPin;
  bool motionDetected;
};

#endif