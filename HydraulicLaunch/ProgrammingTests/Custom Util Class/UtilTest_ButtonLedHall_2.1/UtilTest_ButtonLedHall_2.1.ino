#include <Arduino.h>
#include "PT_Util.h"

Button powerButton(2, Button::TAP);
Led statusLamp(3);
//Timer lampBlink(1000);

int tps = 21;

//unsigned long tempElapsedTime;

void setup() {
  Serial.begin(9600);
}

void loop() {

  powerButton.controlLed(statusLamp, Led::NC);
  //powerButton.isEnabled() ? statusLamp.turnOn() : statusLamp.turnOff();
  
  statusLamp.update();
  delay(1000 / tps);
}
