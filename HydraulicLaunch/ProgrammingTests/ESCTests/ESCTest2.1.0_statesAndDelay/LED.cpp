#include "LED.h"
#include <Arduino.h>

Led::Led() {
    isOn = false;
}

void Led::turnOn() {
    isOn = true;
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(13, HIGH);
}

void Led::turnOff() {
    isOn = false;
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(13, LOW);
}

void Led::blink(int onTime, int offTime) {
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(13, HIGH);
    delay(onTime);
    digitalWrite(13, LOW);
    delay(offTime);
}
