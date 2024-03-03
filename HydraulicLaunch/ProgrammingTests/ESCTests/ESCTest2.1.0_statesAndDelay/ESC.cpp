#include "ESC.h"
#include <Arduino.h>

Esc::Esc() {
    currentSpeed = 0;
}

void Esc::setSpeed(int speed, int escPin) {
    // Assuming you have a function to control ESC speed, replace the following line
    // with your actual implementation
    analogWrite(escPin, speed);  // Assuming ESC control pin is connected to pin 9
}
