#include "Util.h"

Util::Button mainButton(2); // Button attached to pin 2
Util::Led mainLamp(3);        // LED attached to pin 3

void setup() {
}

void loop() {
  // Your loop code
  if (mainButton.isPressed()) {
    mainLamp.turnOn(3); // If the button is pressed, turn the LED on
  } else {
    mainLamp.turnOff(3);  // If the button is not pressed, turn the LED off
  }
}
