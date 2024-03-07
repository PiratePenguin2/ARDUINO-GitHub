// PT_Util::Led implementation
PT_Util::Led::Led(int pin) : ledPin(pin) {
  state = OFF;
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

PT_Util::Led::Led(int pin, int newState) : ledPin(pin), state(newState) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

void PT_Util::Led::update() {
  switch (state) {
    case ON:
      isOn = true;
      digitalWrite(ledPin, HIGH);
      break;
    case OFF:
      isOn = false;
      digitalWrite(ledPin, LOW);
      break;
    case FLIP:
      isOn = !isOn;
      digitalWrite(ledPin, isOn ? HIGH : LOW);
      if (isOn)
        state = ON;
      else
        state = OFF;
      break;
    case BLINK:
      if (blinkTimer.timerFinished())
      {
        Serial.println(blinkTimer.getElapsedTime());
        if (!isOn)
        {
          isOn = true;
          digitalWrite(ledPin, HIGH);
          blinkTimer.setTimer(onTime);
        }
        else
        {
          isOn = false;
          digitalWrite(ledPin, LOW);
          blinkTimer.setTimer(offTime);
          Serial.println();
        }
      }
      break;
    default:
      Serial.println("ERROR: Unknown LED State: " + state);
      break;
  }
}

void PT_Util::Led::setState(int newState) {
  state = newState;
  //update();
}

void PT_Util::Led::setState(int newState, int newOnTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOnTime;
  //update();
}

void PT_Util::Led::setState(int newState, int newOnTime, int newOffTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOffTime;
  //update();
}

void PT_Util::Led::turnOn() {
  state = ON;
  update();
}

void PT_Util::Led::turnOff() {
  state = OFF;
  update();
}

int PT_Util::Led::getState() {
    return state;
}

bool PT_Util::Led::getLampState() {
  return isOn;
}
