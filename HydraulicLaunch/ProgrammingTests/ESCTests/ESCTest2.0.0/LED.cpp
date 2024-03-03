// LED.cpp
#include "LED.h"

LED::LED(int pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}

void LED::turnOn() {
  digitalWrite(ledPin, HIGH);
}

void LED::turnOff() {
  digitalWrite(ledPin, LOW);
}

void LED::blink(int onDuration, int offDuration) {
  turnOn();
  vTaskDelay(pdMS_TO_TICKS(onDuration));
  turnOff();
  vTaskDelay(pdMS_TO_TICKS(offDuration));
}
