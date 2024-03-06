#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2);
PT_Util::Led statusLamp(3);
PT_Util::Timer lampBlink(1000);

int tps = 4;

bool ledState = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  /*if (powerButton.isEnabled()) {  //The button should be latched
    Serial.println("ON");
    statusLamp.turnOn();
  } else {
    Serial.println("OFF");
    statusLamp.turnOff();
  }*/
  Serial.println(lampBlink.getElapsedTime());
  
  if(lampBlink.timerFinished())
  {
    Serial.println("flip");
    ledState = !ledState;
    lampBlink.setTimer(1000);
  }

  if (ledState) {
    statusLamp.turnOn();
  } else {
    statusLamp.turnOff();
  }
  delay(1000 / tps);
}
