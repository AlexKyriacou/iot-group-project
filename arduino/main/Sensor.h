#ifndef Sensor_h
#define Sensor_h

#include <ArduinoJson.h>

class Sensor {
public:
  virtual void setup() = 0;
  virtual bool isDetected();
  virtual float value() { return 0.0f; };
  virtual JsonDocument getJsonData() = 0;
  virtual String getType();
};

#endif