// UtilTest_PanelConfig_1.1.1
#include "EStopButton.h"

EStopButton button1;

void setup() {
  button1.createEStopButton();
}

void loop() {
  button1.EStopButton::update();
}
