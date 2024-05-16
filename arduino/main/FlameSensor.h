#ifndef FlameSensor_h
#define FlameSensor_h

#include "Sensor.h"

class FlameSensor : public Sensor {
public:
  FlameSensor(int flamePin);
  void setup() override;
  bool isDetected() override;
  float value() override;
  JsonDocument getJsonData() override;
  String getType() override;

private:
  int flamePin;
  bool flameDetected;
};

#endif