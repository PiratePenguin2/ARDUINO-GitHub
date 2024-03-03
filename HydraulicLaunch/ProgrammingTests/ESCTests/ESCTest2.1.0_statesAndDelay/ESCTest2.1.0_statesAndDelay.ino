#include "LED.h"
#include "ESC.h"
#include "Launch.h"

Launch launch;

// Button pin
const int buttonPin = 2; // Change this to the pin you are using for the button

void setup() {
    Serial.begin(9600);

    // Initialize button pin
    pinMode(buttonPin, INPUT_PULLUP);

    // Wait for the button to be pressed before starting the launch sequence
    while (digitalRead(buttonPin) == HIGH) {
        delay(100);
    }

    launch.startSequence();
}

void loop() {
    // Your main loop code here
    // This loop can handle other tasks while waiting for the button press
}
