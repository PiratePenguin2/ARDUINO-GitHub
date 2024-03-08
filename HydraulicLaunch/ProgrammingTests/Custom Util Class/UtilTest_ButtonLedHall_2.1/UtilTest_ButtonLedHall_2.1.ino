#include <Arduino.h>
#include "PT_Util.h"

Button powerButton(2, Button::PUSH);
Led statusLamp(3, Led::BLINK, Led::NC);
//Timer lampBlink(1000);

int tps = 21;

//unsigned long tempElapsedTime;

void setup() {
  Serial.begin(9600);
  //statusLamp.setLedMode(Led::NO);
  statusLamp.setLedState(Led::BLINK, 250);
}

void loop() {

  powerButton.controlLed(statusLamp);
  //powerButton.isEnabled() ? statusLamp.turnOn() : statusLamp.turnOff();
  
  statusLamp.update();
  delay(1000 / tps);
}
