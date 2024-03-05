#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2, LATCH);
PT_Util::Led statusLamp(3);

void setup() {
  // Your setup code
}

void loop() {
  if (powerButton.isEnabled()) {  //The button should be latched
    statusLamp.turnOn();
  } else {
    statusLamp.turnOff();
  }
}
