#include <Arduino.h>
#include "PT_Util.h"

Button powerButton(2, Button::PUSH);
Led statusLamp(10, Led::BLINK, Led::NO);

//Button toggleBrakes(4, Button::PUSH);
Led brakesRed(9, Led::BLINK, Led::NC);
Led brakesGreen(11, Led::BLINK, Led::NC);
Led brakesBlue(12, Led::BLINK, Led::NC);

//Timer lampBlink(1000);

int tps = 21;

//unsigned long tempElapsedTime;

void setup() {
  Serial.begin(9600);
  //statusLamp.setLedMode(Led::NO);
  statusLamp.setLedState(Led::BLINK, 250);
  
  brakesRed.setLedState(Led::BLINK, 250);
  brakesGreen.setLedState(Led::BLINK, 250);
  brakesBlue.setLedState(Led::BLINK, 250);
}

void loop() {

  powerButton.controlLed(statusLamp);//, Led::ON, Led::BLINK);
  //statusLamp.update();
  
  brakesRed.update();
  brakesGreen.update();
  brakesBlue.update();
  delay(1000 / tps);
}
