#include "MyPCF8574.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#define PCF8574_ADDR1 0x20 // Buttons (8 buttons)
#define PCF8574_ADDR2 0x21 // Buttons (8 buttons)
#define PCF8574_ADDR3 0x22 // DC motor IN pins (2 motors + 2 sensors)
#define PCF8574_ADDR4 0x23 // DC motor IN pins (2 motors + 2 sensors)
#define PCF8574_ADDR5 0x24 // DC motor IN pins (2 motors + 2 sensors)
#define PCF8574_ADDR6 0x25 // DC motor IN pins (2 motors + 2 sensors)
#define PCF8574_ADDR7 0x26 // DC motor IN pins (2 motors + 2 sensors)

#define PCA9685_ADDR1 0x40 // First PCA9685 board (PWM for 6 DC motors and 6 servos)
#define PCA9685_ADDR2 0x41 // Second PCA9685 board (PWM for 4 DC motors and 4 servos)

// Define DC motor control channels on PCA9685 #1 and #2
#define DRIVETIRE_A1 0 // On PCA9685 #1
#define DRIVETIRE_A2 1 // On PCA9685 #1
#define DRIVETIRE_A3 2 // On PCA9685 #1
#define DRIVETIRE_A4 3 // On PCA9685 #1
#define DRIVETIRE_B1 0 // On PCA9685 #2
#define DRIVETIRE_B2 1 // On PCA9685 #2
#define DRIVETIRE_B3 2 // On PCA9685 #2
#define DRIVETIRE_B4 3 // On PCA9685 #2
#define DRIVETIRE_B5 4 // On PCA9685 #2
#define DRIVETIRE_B6 5 // On PCA9685 #2

// Define servo channels on PCA9685 #1 and #2
#define SERVO_A1 8  // On PCA9685 #1
#define SERVO_A2 9  // On PCA9685 #1
#define SERVO_A3 10 // On PCA9685 #1
#define SERVO_A4 11 // On PCA9685 #1
#define SERVO_B1 8  // On PCA9685 #2
#define SERVO_B2 9  // On PCA9685 #2
#define SERVO_B3 10 // On PCA9685 #2
#define SERVO_B4 11 // On PCA9685 #2
#define SERVO_B5 12 // On PCA9685 #2
#define SERVO_B6 13 // On PCA9685 #2

Adafruit_PWMServoDriver pca9685_1 = Adafruit_PWMServoDriver(PCA9685_ADDR1);
Adafruit_PWMServoDriver pca9685_2 = Adafruit_PWMServoDriver(PCA9685_ADDR2);

Servo servos[10];

// Instantiate MyPCF8574 objects
MyPCF8574 pcf8574_1(PCF8574_ADDR1);
MyPCF8574 pcf8574_2(PCF8574_ADDR2);
MyPCF8574 pcf8574_3(PCF8574_ADDR3);
MyPCF8574 pcf8574_4(PCF8574_ADDR4);
MyPCF8574 pcf8574_5(PCF8574_ADDR5);
MyPCF8574 pcf8574_6(PCF8574_ADDR6);
MyPCF8574 pcf8574_7(PCF8574_ADDR7);

void setup() {
  Wire.begin();
  
  // Initialize PCA9685 boards
  pca9685_1.begin();
  pca9685_1.setPWMFreq(60);
  pca9685_2.begin();
  pca9685_2.setPWMFreq(60);
  
  // Attach servos to PCA9685 boards
  servos[0].attach(0); // Attach to channel 0 of PCA9685 #1
  servos[1].attach(1); // Attach to channel 1 of PCA9685 #1
  servos[2].attach(2); // Attach to channel 2 of PCA9685 #1
  servos[3].attach(3); // Attach to channel 3 of PCA9685 #1
  servos[4].attach(4); // Attach to channel 0 of PCA9685 #2
  servos[5].attach(5); // Attach to channel 1 of PCA9685 #2
  servos[6].attach(6); // Attach to channel 2 of PCA9685 #2
  servos[7].attach(7); // Attach to channel 3 of PCA9685 #2

  // Initialize PCF8574 boards
  pcf8574_1.begin();
  pcf8574_2.begin();
  pcf8574_3.begin();
  pcf8574_4.begin();
  pcf8574_5.begin();
  pcf8574_6.begin();
  pcf8574_7.begin();
}

void loop() {
  // Read the state of the buttons
  uint8_t buttonState1 = pcf8574_1.read8();
  uint8_t buttonState2 = pcf8574_2.read8();

  // Read the state of the hall effect sensors
  uint8_t hallEffectState1 = pcf8574_3.read8();
  uint8_t hallEffectState2 = pcf8574_4.read8();
  uint8_t hallEffectState3 = pcf8574_5.read8();
  uint8_t hallEffectState4 = pcf8574_6.read8();

  // Read the state of the motor control pins
  uint8_t motorInState_1 = pcf8574_3.read8();
  uint8_t motorInState_2 = pcf8574_4.read8();
  uint8_t motorInState_3 = pcf8574_5.read8();
  uint8_t motorInState_4 = pcf8574_6.read8();
  uint8_t motorInState_5 = pcf8574_7.read8();

  // Use the button states, hall effect sensor states, and motor control states in your logic
  // Example: If button 1 is pressed
  if (buttonState1 & 0x01) {
    // Do something, like move a servo
    servos[0].write(90); // Move servo to 90 degrees
  }
}
