#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_PCF8574.h>
#include "PTservo.h"
#include "PTdcmotor.h"


// Create PCA9685 objects for different boards
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);  // PCA9685 at address 0x40
Adafruit_PCF8574 pcf1;

// Create motor and servo objects
PTdcmotor tireA = PTdcmotor(pwm1, 0);
PTdcmotor tireB = PTdcmotor(pwm1, 1);
PTservo servoA  = PTservo(pwm1, 8);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize I2C communication and each PCF8574
  Serial.println("\nInitializing PCF8574 Boards");
  initializeBoard(pcf1, 0x20);
  Serial.println("All PCF8574 Boards Initiated!\n");

  // Initialize PCA9685 boards
  Serial.println("Initializing PCA9685 Boards");
  initializeBoard(pwm1, 50);  // Initialize PCA9685 at address 0x40
  Serial.println("All PCA9685 Boards Initiated!\n");

  tireA.initializePins(0, 1, pcf1);
  tireB.initializePins(2, 3, pcf1);

  // Start with motors stopped
  tireA.write(0);
  tireB.write(0);
  servoA.write(90); // Set servo to initial position (90 degrees)
}

void loop() {
  Serial.print("A_");
  tireA.write(100);
  tireB.write(100);
  servoA.write(180);

  delay(2000);  // Run forward for 2 seconds

  tireA.write(0);
  tireB.write(0);
  servoA.write(90);

  delay(1000);  // Stop for 1 second

  tireA.write(-100);
  tireB.write(-100);
  servoA.write(0);

  delay(2000);  // Run backward for 2 seconds

  tireA.write(0);
  tireB.write(0);
  servoA.write(90);

  delay(1000);  // Stop for 1 second
}





// Function to initialize PCF8574 boards
void initializeBoard(Adafruit_PCF8574& pcf, uint8_t addr) {
  if (!pcf.begin(addr)) {
    Serial.print("Couldn't find PCF8574 at address 0x");
    Serial.println(addr, HEX);
    while (1);
  }
}

// Function to initialize PCA9685 boards with frequency and address
void initializeBoard(Adafruit_PWMServoDriver &pwmBoard, int freq) {
    pwmBoard.begin();
    pwmBoard.setPWMFreq(freq);
}
