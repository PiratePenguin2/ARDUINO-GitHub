#include "Util.h"

Util::Button powerButton(2); // Power button attached to pin 2
Util::Led statusLamp(3);      // Status LED attached to pin 3

void setup() {
  
}

void loop() {
  if (powerButton.isPressed()) {
    statusLamp.turnOn(); // If the button is pressed, turn the LED on
  } else {
    statusLamp.turnOff();  // If the button is not pressed, turn the LED off
  }
}
