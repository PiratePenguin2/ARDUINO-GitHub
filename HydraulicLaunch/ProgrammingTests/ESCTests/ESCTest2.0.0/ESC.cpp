// ESC.cpp
#include "ESC.h"
#include "LERP.h"

ESC::ESC(int pin) {
  escPin = pin;
  pinMode(escPin, OUTPUT);
}

void ESC::attach() {
  escName.attach(escPin);
}

bool ESC::newTarget(int target) {
  targetSpeed = target;
  return true;
}

void ESC::updateSpeed(float smooth) {
  smoothSpeed = lerp(smoothSpeed, targetSpeed, smooth);
  Serial.print("smoothSpeed: ");
  Serial.print(smoothSpeed);
  Serial.print(", targetSpeed: ");
  Serial.print(targetSpeed);
  Serial.print(", lerp result: ");
  Serial.println(lerp(smoothSpeed, targetSpeed, smooth));

  smoothSpeed = map(smoothSpeed, 0, 1023, 90, 180);   // scale it to use it with the servo library (value between 0 and 180)
  escName.write(static_cast<int>(smoothSpeed));    // Send the signal to the ESC
}
