// PT_Util::Button implementation
PT_Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
  mode = PUSH;  // Set default mode
}

PT_Util::Button::Button(int pin, int mode) : buttonPin(pin), mode(mode) {
  pinMode(buttonPin, INPUT);
}

/*void PT_Util::Button::controlLed(PT_Util::Led led)
{
  this.isEnabled() ? statusLamp.turnOn() : statusLamp.turnOff();
}

void PT_Util::Button::controlLed(PT_Util::Led led, int ledMode)
{
  switch (ledMode) {
    case NORMALLY_OPEN:
    case NO:
      this.isEnabled() ? statusLamp.turnOn() : statusLamp.turnOff();
      break;
    case NORMALLY_CLOSED:
    case NC:
      this.isEnabled() ? statusLamp.turnOff() : statusLamp.turnOn();
      break;
    default:
      Serial.println("Unknown Button-Controlled Led Mode: " + ledMode);
      break;
  } //Switch
}*/

bool PT_Util::Button::isPressed() {
  return (digitalRead(buttonPin) == LOW);
}

bool PT_Util::Button::isEnabled() {
  bool isPushed = isPressed();
  switch (mode) {
    case PUSH:
      enabled = isPushed;
      break;
    case TAP:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = true;
        buttonDelay.setTimer(500);
      } else {
        enabled = false;
      }
      break;
    case TAP_RELEASE:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = true;
        buttonDelay.setTimer(500);
      } else {
        enabled = false;
      }
      break;
    case LATCH:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = !enabled;
        buttonDelay.setTimer(500);
      }
      break;
    default:
      Serial.println("Unknown Button Mode: " + mode);
      break;
    lastPushed = isPushed;
  };
  return enabled;
}
