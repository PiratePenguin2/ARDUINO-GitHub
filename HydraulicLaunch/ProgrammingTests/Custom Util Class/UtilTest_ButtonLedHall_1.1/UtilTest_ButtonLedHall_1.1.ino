#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2);
PT_Util::Led statusLamp(3);
PT_Util::Timer lampBlink(1000);

int tps = 21;

//unsigned long tempElapsedTime;

void setup() {
  Serial.begin(9600);
}

void loop() {

  //statusLamp.setState(BLINK, 250, 250);

  if (lampBlink.timerFinished())
  {
    Serial.println("works?");
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
  

  }
  statusLamp.update();
  delay(1000 / tps);
}
