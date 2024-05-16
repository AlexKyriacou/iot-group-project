#ifndef GasSensor_h
#define GasSensor_h

#include "Sensor.h"

class GasSensor : public Sensor {
public:
  GasSensor(int gasPin);
  void setup() override;
  bool isDetected() override;
  float value() override;
  JsonDocument getJsonData() override;
  String getType() override;

private:
  int gasPin;
  bool gasDetected;
};

#endif