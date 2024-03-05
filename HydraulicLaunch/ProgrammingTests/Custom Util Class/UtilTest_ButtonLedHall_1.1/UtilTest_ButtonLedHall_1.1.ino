#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2);
PT_Util::Led statusLamp(3);

void setup() {
  // Your setup code
}

void loop() {
  if (powerButton.isPressed()) {
    statusLamp.turnOn();
  } else {
    statusLamp.turnOff();
  }
}
