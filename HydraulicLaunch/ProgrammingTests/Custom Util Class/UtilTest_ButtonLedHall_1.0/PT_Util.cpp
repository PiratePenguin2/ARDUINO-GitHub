#include "PT_Util.h"

/**
 * @brief Constructor for the Button class.
 * 
 * @param pin The pin to which the button is connected.
 */
PT_Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
}

/**
 * @brief Check if the button is pressed.
 * 
 * @return true if the button is pressed, false otherwise.
 */
bool PT_Util::Button::isPressed() {
  return digitalRead(buttonPin) == LOW;
}

/**
 * @brief Constructor for the Led class.
 * 
 * @param pin The pin to which the LED is connected.
 */
PT_Util::Led::Led(int pin) : ledPin(pin) {
  pinMode(ledPin, OUTPUT); // Set the LED pin as OUTPUT in the constructor
  isOn = false;
}

/**
 * @brief Turn the LED on.
 */
void PT_Util::Led::turnOn() {
  isOn = true;
  digitalWrite(ledPin, HIGH);
}

/**
 * @brief Turn the LED off.
 */
void PT_Util::Led::turnOff() {
  isOn = false;
  digitalWrite(ledPin, LOW);
}

/**
 * @brief Blink the LED with specified on and off times.
 * 
 * @param onTime Duration for the LED to be on.
 * @param offTime Duration for the LED to be off.
 */
void PT_Util::Led::blink(int onTime, int offTime) {
  digitalWrite(ledPin, HIGH);
  delay(onTime);
  digitalWrite(ledPin, LOW);
  delay(offTime);
}

/**
 * @brief Constructor for the HallEffectSensor class.
 * 
 * @param pin The pin to which the Hall Effect Sensor is connected.
 */
PT_Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

/**
 * @brief Read the state of the Hall Effect Sensor.
 * 
 * @return The state of the Hall Effect Sensor.
 */
int PT_Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
