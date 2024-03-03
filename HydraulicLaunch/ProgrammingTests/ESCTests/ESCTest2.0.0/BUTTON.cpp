// BUTTON.cpp
#include "BUTTON.h"

Button::Button(int pin) {
  buttonPin = pin;
  pinMode(buttonPin, INPUT);
}

bool Button::isPressed() {
  return digitalRead(buttonPin) == HIGH;
}
