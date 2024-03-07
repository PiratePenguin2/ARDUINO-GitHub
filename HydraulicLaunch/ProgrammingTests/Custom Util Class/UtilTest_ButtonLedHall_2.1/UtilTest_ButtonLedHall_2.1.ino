#include <Arduino.h>
#include "PT_Util.h"

Button powerButton(2, LATCH);
Led statusLamp(3);
//Timer lampBlink(1000);

int tps = 21;

//unsigned long tempElapsedTime;

void setup() {
  Serial.begin(9600);
}

void loop() {

  //powerButton.controlLed(statusLamp);
  powerButton.isEnabled() ? statusLamp.turnOn() : statusLamp.turnOff();
  
  statusLamp.update();
  delay(1000 / tps);
}




  /*
  //statusLamp.setState(BLINK, 250, 250);

  if (lampBlink.timerFinished())
  {
    if (statusLamp.getState() == OFF)
    {
      statusLamp.setState(BLINK, 250);
      lampBlink.setTimer(5000);
    }
    else if (statusLamp.getState() == BLINK)
    {
      statusLamp.turnOff();
      lampBlink.setTimer(5000);
    }
    else
    {
      statusLamp.turnOn();
    }
  }*/
