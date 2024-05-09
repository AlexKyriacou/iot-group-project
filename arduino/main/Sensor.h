#ifndef Sensor_h
#define Sensor_h

#include <ArduinoJson.h>

class Sensor {
public:
  virtual void setup() = 0;
  virtual bool isDetected() = 0;
  virtual JsonDocument getJsonData() = 0;
};

#endif