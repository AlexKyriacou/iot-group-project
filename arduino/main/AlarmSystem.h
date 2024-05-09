#include "Sensor.h"
#include "Led.h"
#include "CommandManager.h"

#define MAX_SENSORS 5

class AlarmSystem {
public:
  AlarmSystem(int ledPin);
  void addSensor(Sensor* sensor);
  void setup();
  void loop();
  void handleCommand(const String& command);

private:
  Sensor* sensors[MAX_SENSORS];
  int numSensors;
  Led motionLed;
  bool alarmArmed;
  unsigned long lastPrintTime;

  void updateMotionLed();
  void printSensorStatus();
};