#include "LED.h"
#include <Arduino.h>

Led::Led() {
    isOn = false;
}

void Led::turnOn(int ledPin) {
    isOn = true;
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(ledPin, HIGH);
}

void Led::turnOff(int ledPin) {
    isOn = false;
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(ledPin, LOW);
}

void Led::blink(int ledPin, int onTime, int offTime) {
    // Assuming you are using an LED connected to a pin, replace 13 with your actual pin
    digitalWrite(ledPin, HIGH);
    delay(onTime);
    digitalWrite(ledPin, LOW);
    delay(offTime);
}
