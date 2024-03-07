#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2);
PT_Util::Led statusLamp(3);
PT_Util::Timer lampBlink(1000);

int tps = 4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(lampBlink.getElapsedTime());
  
  if(lampBlink.timerFinished())
  {
    Serial.print("flip - Elapsed Time: ");
    Serial.println(lampBlink.getElapsedTime());
    statusLamp.setState(FLIP);
    lampBlink.setTimer(1000);
  }
  
  delay(1000 / tps);
}
