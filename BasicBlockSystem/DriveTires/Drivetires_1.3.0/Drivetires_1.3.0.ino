#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "DC_Motor.h"

// Create PWM driver instances
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

// Declare motors with short identifiers
DC_Motor L7(&pwm1, 0, 1);  // Motor connected to pwm1 pins 0 and 1
DC_Motor U5(&pwm1, 2, 3);  // Motor connected to pwm1 pins 2 and 3
DC_Motor A9(&pwm2, 4, 5);  // Motor connected to pwm2 pins 4 and 5

void setup() {
    pwm1.begin();
    pwm2.begin();
    
    pwm1.setPWMFreq(1600);  // Set frequency for PCA9685
    pwm2.setPWMFreq(1600);
    
    Wire.setClock(400000);  // Set I2C speed to 400kHz
}

void loop() {
    // Set motor speeds
    L7.setSpeed(50);   // Forward at 50% speed
    U5.setSpeed(-100); // Full reverse
    A9.setSpeed(0);    // Stop
    delay(1000);
    
    // Reverse directions
    L7.setSpeed(-50);  // Reverse at 50% speed
    U5.setSpeed(100);  // Full forward
    A9.setSpeed(0);    // Stop
    delay(1000);
}
