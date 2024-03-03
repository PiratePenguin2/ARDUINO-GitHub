#include "Launch.h"
#include <Arduino.h>

Launch::Launch() {
    // Initialize your Launch class here if needed
}

void Launch::printState(const char* state, int duration) {
    Serial.print("State: ");
    Serial.print(state);
    Serial.print(" (");
    if (duration > 0) {
        Serial.print(duration);
        Serial.print(" ms)");
    } else {
        Serial.print("N/A)");
    }
    Serial.println();
}

void Launch::setState(const char* state, int duration) {
    printState(state, duration);
    delay(duration);
}

void Launch::startSequence() {
    // Initial state
    setState("IDLE", 0);

    // Set to "LAUNCHREADY" in setup
    setState("LAUNCHREADY", 0);

    // Set to "LAUNCHREADY" before launch
    setState("LAUNCHREADY", 0);
    led.blink(blinkRate1, blinkRate1);

    // PRESTAGING
    setState("PRESTAGING", 100);
    // PRESTAGED
    setState("PRESTAGED", 0);
    led.blink(blinkRate2, blinkRate2);

    // STAGING
    setState("STAGING", 1000);

    // STAGED
    setState("STAGED", 0);
    led.turnOn();

    // LAUNCHING
    setState("LAUNCHING", 150);
    esc.setSpeed(200);
    led.blink(rapidBlinkRate, rapidBlinkRate);

    // DECELERATING
    setState("DECELERATING", 0);
    esc.setSpeed(-200);
    led.turnOn();

    // TRAINASCEND
    setState("TRAINASCEND", 2000);
    led.blink(400, 400);
    // Add comment for raising brakes

    // STARTRESET
    setState("STARTRESET", 0);
    
    // RESET
    setState("RESET", 0);

    // INTERVAL
    setState("INTERVAL", 1000);

    // Back to LAUNCHREADY
    setState("LAUNCHREADY", 0);
}
