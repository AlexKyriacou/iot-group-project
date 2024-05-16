#include "Sensor.h"
#include "Alarm.h"
#include "CommandManager.h"

#define MAX_SENSORS 5

class AlarmSystem {
public:
  AlarmSystem(int aKLedPin, int aWLedPin, int mMBuzzerPin);
  void addSensor(Sensor* sensor);
  void setup();
  void loop();
  void handleCommand(const String& command);

private:
  Sensor* sensors[MAX_SENSORS];
  int numSensors;
  Alarm aKLed;
  Alarm aWLed;
  Alarm mMBuzzer;
  bool alarmArmed;
  int gasThreshold;
  int flameThreshold;
  int distanceThreshold;
  unsigned long lastPrintTime;

  void updateAlarms();
  void printSensorStatus();
};