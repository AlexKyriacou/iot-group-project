class Alarm {
private:
  int pin;
  int state;

public:
  Alarm(int pin);
  void setup();
  void on();
  void off();
  void toggle();
};
