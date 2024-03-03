// LAUNCH.cpp
#include "LAUNCH.h"

Launch::Launch(int escPin, int ledPin, int buttonPin)
    : esc(escPin), led(ledPin), button(buttonPin) {
}

void Launch::initialize() {
  currentState = IDLE;
  updateState();
}

void Launch::updateState() {
  Serial.print("Launch State: ");
  Serial.print(stateNames[currentState]);
  Serial.print(" (Duration: ");
  Serial.print(stateDurations[currentState]);
  Serial.println(" ms)");

  switch (currentState) {
    case IDLE:
      esc.newTarget(0);
      led.turnOff();
      break;

    case LAUNCHREADY:
      esc.newTarget(0);
      led.blink(750, 750);
      break;

    case PRESTAGING:
      esc.newTarget(0);
      led.turnOff();
      vTaskDelay(pdMS_TO_TICKS(stateDurations[PRESTAGING]));
      currentState = PRESTAGED;
      break;

    case PRESTAGED:
      led.blink(250, 250);
      break;

    case STAGING:
      led.blink(250, 250);
      vTaskDelay(pdMS_TO_TICKS(stateDurations[STAGING]));
      currentState = STAGED;
      break;

    case STAGED:
      led.turnOn();
      break;

    case LAUNCHING:
      esc.newTarget(200);
      led.blink(50, 50);
      vTaskDelay(pdMS_TO_TICKS(stateDurations[LAUNCHING]));
      currentState = DECELERATING;
      break;

    case DECELERATING:
      esc.newTarget(-200);
      led.turnOn();
      currentState = TRAINASCEND;
      break;

    case TRAINASCEND:
      esc.newTarget(0);
      led.blink(400, 400);
      // Add comment for raising brakes
      currentState = STARTRESET;
      break;

    case STARTRESET:
      // Placeholder for future functionality
      currentState = RESET;
      break;

    case RESET:
      // Placeholder for future functionality
      currentState = INTERVAL;
      break;

    case INTERVAL:
      esc.newTarget(0);
      led.turnOff();
      vTaskDelay(pdMS_TO_TICKS(stateDurations[INTERVAL]));
      currentState = LAUNCHREADY;
      break;
  }
}

void Launch::startLaunch() {
  if (currentState == LAUNCHREADY) {
    currentState = PRESTAGING;
    updateState();
  } else if (currentState == STAGED) {
    currentState = LAUNCHING;
    updateState();
  }
}
