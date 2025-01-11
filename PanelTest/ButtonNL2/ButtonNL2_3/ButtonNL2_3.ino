#include <Keyboard.h>  // Ensure this is included for HID functionality

class Sensor {
  private:
    uint8_t _pin;  // Pin number
    bool _oldState;  // Previous state
    bool _currentState;  // Current state
    unsigned long lastDebounceTime;  // Last debounce time
    const unsigned long debounceDelay = 100;  // Debounce delay in milliseconds

  public:
    // Constructor
    Sensor(uint8_t pin) : _pin(pin), _oldState(HIGH), _currentState(HIGH), lastDebounceTime(0) {
      pinMode(pin, INPUT_PULLUP);  // Set pin as input with internal pull-up resistor
    }

    // Update method to handle debouncing and state changes
    void update() {
  bool reading = digitalRead(_pin);  // Read current state of the pin
  Serial.print("Pin: ");
  Serial.print(_pin);
  Serial.print(" Current Reading: ");
  Serial.println(reading);

  // Check if the pin state has changed
  if (reading != _oldState) {
    lastDebounceTime = millis();
    Serial.print("Pin: ");
    Serial.print(_pin);
    Serial.println(" State Changed (Debouncing)");
  }

  // If state is stable for longer than the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    Serial.print("Pin: ");
    Serial.print(_pin);
    Serial.print(" Stable Reading: ");
    Serial.println(reading);

    if (reading != _currentState) {
      Serial.println("Check 1");  // Debug statement

      _currentState = reading;  // Update the current state

      Serial.println("Check 2");  // Debug statement

      // Print debug info for state change
      Serial.print("Pin: ");
      Serial.print(_pin);
      Serial.print(" State Changed - OldState: ");
      Serial.print(_oldState);
      Serial.print(", CurrentState: ");
      Serial.println(_currentState);

      Serial.println("Check 3");  // Debug statement

      // Take action based on the new state
      if (_currentState == LOW) {
        Serial.println("Key ON pushed");
        // Keyboard.press('8');
        // Keyboard.release('8');
      } else {
        Serial.println("Key OFF pushed");
        // Keyboard.press('2');
        // Keyboard.release('2');
      }

      Serial.println("Check 4");  // Debug statement
    }

    // Always update the old state after the debounce check
    _oldState = reading;
  }
}

};

// Declare the Sensor objects globally
Sensor keyL(2);  // Sensor on pin 2
Sensor keyR(3);  // Sensor on pin 3

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize keyboard (if applicable)
  Keyboard.begin();
}

void loop() {
  // Call update for each sensor to check their states
  keyL.update();
  keyR.update();

  // Small delay to reduce processor load
  delay(10);
}
