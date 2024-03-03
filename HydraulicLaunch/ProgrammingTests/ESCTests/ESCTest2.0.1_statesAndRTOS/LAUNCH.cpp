// LAUNCH.cpp
#include "LAUNCH.h"
#include "LED.h"

LAUNCH::LAUNCH() : state("IDLE"), escSpeed(0), ledPin(13) {}

void LAUNCH::initialize() {
    // Initialize components
    led.initialize();
}

void LAUNCH::startLaunchSequence() {
    setState("LAUNCHREADY");
    // Additional setup for launch sequence if needed
}

void LAUNCH::update() {
    // Update the state and perform actions based on the current state
    if (state == "IDLE") {
        // Handle IDLE state
        escSpeed = 0;
        led.turnOff();
    } else if (state == "LAUNCHREADY") {
        // Handle LAUNCHREADY state
        escSpeed = 0;
        led.blink(750, 750);
    } else if (state == "PRESTAGING") {
        // Handle PRESTAGING state
        escSpeed = 0;
        led.turnOff();
        vTaskDelay(100 / portTICK_PERIOD_MS);  // FreeRTOS wait
        setState("PRESTAGED", 0);  // Immediate transition to PRESTAGED
    } else if (state == "PRESTAGED") {
        // Handle PRESTAGED state
        led.blink(250, 250);
    } else if (state == "STAGING") {
        // Handle STAGING state
        escSpeed = 0;
        // Additional STAGING logic
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // FreeRTOS wait
        setState("STAGED", 0);  // Immediate transition to STAGED
    } else if (state == "STAGED") {
        // Handle STAGED state
        led.turnOn();
    } else if (state == "LAUNCHING") {
        // Handle LAUNCHING state
        escSpeed = 200;
        led.blink(50, 50);
        vTaskDelay(150 / portTICK_PERIOD_MS);  // FreeRTOS wait
        setState("DECELERATING", 0);  // Immediate transition to DECELERATING
    } else if (state == "DECELERATING") {
        // Handle DECELERATING state
        escSpeed = -200;
        led.turnOn();
    } else if (state == "TRAINASCEND") {
        // Handle TRAINASCEND state
        escSpeed = 0;
        led.blink(400, 400);
        // Additional TRAINASCEND logic
        vTaskDelay(2000 / portTICK_PERIOD_MS);  // FreeRTOS wait
        setState("STARTRESET", 0);  // Immediate transition to STARTRESET
    } else if (state == "STARTRESET") {
        // Handle STARTRESET state
        // Placeholder for future logic
        setState("RESET", 0);  // Immediate transition to RESET
    } else if (state == "RESET") {
        // Handle RESET state
        // Placeholder for future logic
        setState("INTERVAL", 0);  // Immediate transition to INTERVAL
    } else if (state == "INTERVAL") {
        // Handle INTERVAL state
        escSpeed = 0;
        led.turnOff();
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // FreeRTOS wait
        setState("LAUNCHREADY", 0);  // Immediate transition to LAUNCHREADY
    }

    // Debugging: print state and time
    Serial.print("State: ");
    Serial.print(state);
    Serial.print(" (");
    Serial.print(stateDuration);
    Serial.println(")");
}

void LAUNCH::setState(String newState, int duration) {
    state = newState;
    stateStartTime = millis();
    stateDuration = duration;
}
