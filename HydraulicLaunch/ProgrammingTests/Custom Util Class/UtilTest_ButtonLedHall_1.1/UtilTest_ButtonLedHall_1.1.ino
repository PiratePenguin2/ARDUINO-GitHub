#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button powerButton(2);
PT_Util::Led statusLamp(3);

int tps = 4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (powerButton.isEnabled()) {  //The button should be latched
    Serial.println("ON");
    statusLamp.turnOn();
  } else {
    Serial.println("OFF");
    statusLamp.turnOff();
  }
  delay(1000 / tps);
}
