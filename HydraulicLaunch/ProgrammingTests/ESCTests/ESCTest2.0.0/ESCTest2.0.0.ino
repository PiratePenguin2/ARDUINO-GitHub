// Main, ESCTest2.0.0

#include "ESC.h"
#include "LAUNCH.h"
#include "BUTTON.h"
#include <FreeRTOS.h>

const int buttonPin = 2;
const int escPin = 12;
const int ledPin = 3;
const int fps = 20;

ESC motor(escPin);
Launch launch(escPin, ledPin, buttonPin);
Button launchButton(buttonPin);

void setup() {
  motor.attach();
  launch.initialize();
  Serial.begin(9600);
}

void loop() {
  // Check button every 1000/fps milliseconds
  vTaskDelay(pdMS_TO_TICKS(1000 / fps));

  if (launchButton.isPressed()) {
    launch.startLaunch();
  }

  // Existing loop logic...

  motor.updateSpeed(1);
}
