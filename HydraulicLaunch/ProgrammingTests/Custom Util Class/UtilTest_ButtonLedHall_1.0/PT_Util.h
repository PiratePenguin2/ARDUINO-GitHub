#pragma once
#include <Arduino.h>

/**
 * @brief PT_Util class containing various utility functions and classes.
 */
class PT_Util {
public:
  /**
   * @brief Button class representing a simple button with methods to check if it's pressed.
   */
  class Button {
  public:
    /**
     * @brief Constructor for the Button class.
     * 
     * @param pin The pin to which the button is connected.
     */
    Button(int pin);

    /**
     * @brief Check if the button is pressed.
     * 
     * @return true if the button is pressed, false otherwise.
     */
    bool isPressed();

    int buttonPin; /**< The pin to which the button is connected. */
  };

  /**
   * @brief Led class representing an LED with methods to control its state.
   */
  class Led {
  public:
    /**
     * @brief Constructor for the Led class.
     * 
     * @param pin The pin to which the LED is connected.
     */
    Led(int pin);

    /**
     * @brief Turn the LED on.
     */
    void turnOn();

    /**
     * @brief Turn the LED off.
     */
    void turnOff();

    /**
     * @brief Blink the LED with specified on and off times.
     * 
     * @param onTime Duration for the LED to be on.
     * @param offTime Duration for the LED to be off.
     */
    void blink(int onTime, int offTime);

  private:
    bool isOn; /**< Flag indicating the LED state. */
    int ledPin; /**< The pin to which the LED is connected. */
  };

  /**
   * @brief HallEffectSensor class representing a Hall Effect Sensor with methods to read its state.
   */
  class HallEffectSensor {
  public:
    /**
     * @brief Constructor for the HallEffectSensor class.
     * 
     * @param pin The pin to which the Hall Effect Sensor is connected.
     */
    HallEffectSensor(int pin);

    /**
     * @brief Read the state of the Hall Effect Sensor.
     * 
     * @return The state of the Hall Effect Sensor.
     */
    int readSensorValue();

  private:
    int sensorPin; /**< The pin to which the Hall Effect Sensor is connected. */
  };
};
