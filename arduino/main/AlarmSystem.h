#include "MotionDetector.h"
#include "Led.h"
#include "CommandManager.h"

class AlarmSystem {
public:
  AlarmSystem(int pirPin, int ledPin);
  void setup();
  void loop();
  void handleCommand(const String &command);

private:
  MotionDetector motionDetector;
  Led motionLed;
  bool alarmArmed;
  unsigned long lastPrintTime;

  void updateMotionLed();
  void printMotionStatus();
};
