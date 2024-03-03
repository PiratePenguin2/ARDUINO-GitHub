// ESC.h
#ifndef ESC_h
#define ESC_h

#include <Arduino.h>
#include <Servo.h>

class ESC {
private:
  Servo escName;
  int escPin;
  float targetSpeed;
  float smoothSpeed;

public:
  ESC(int pin);
  void attach();
  bool newTarget(int target);
  void updateSpeed(float speedSmoothing);
};

#endif
