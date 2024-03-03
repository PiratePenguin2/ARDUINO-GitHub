#include "LED.h"
#include "ESC.h"
#include "Launch.h"

Launch launch;

// Button pin
const int buttonPin = 2; // Change this to the pin you are using for the button
// LED pin
const int ledPin = 3;
// Esc Pin
const int escPin = 12;

void setup() {
    Serial.begin(9600);

    // Initialize button pin
    pinMode(buttonPin, INPUT_PULLUP);

    launch.startSequence(escPin, ledPin);
}

void loop() {
    // Your main loop code here
    // This loop can handle other tasks while waiting for the button press
}
