#ifndef UltraSonicSensor_h
#define UltraSonicSensor_h

#include "Sensor.h"

class UltraSonicSensor : public Sensor {
public:
  UltraSonicSensor(int trigPin, int echoPin);
  void setup() override;
  bool isDetected() override;
  float value() override;
  JsonDocument getJsonData() override;
  String getType() override;

private:
  int trigPin;
  int echoPin;
  bool tooClose;
};

#endif