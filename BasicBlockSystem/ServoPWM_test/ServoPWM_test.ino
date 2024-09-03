3#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object using the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define the channel for the servo (0-15) 320 mid, +-225
#define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  545 // This is the 'maximum' pulse length count (out of 4096)
//#define USMIN  600    // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
//#define USMAX  2400   // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servoChannel = 8; // Servo connected to channel 0
uint8_t servoChannel2 = 9;
uint8_t servoChannel3 = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test");

  // Initialize the PCA9685 with the default I2C address
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servoChannel, 0, pulselen);
    pwm.setPWM(servoChannel2, 0, pulselen);
    pwm.setPWM(servoChannel3, 0, pulselen);
    if (pulselen == 320)
    {
      delay(500);
    }
    delay(10);
  }

  delay(500);

  // Sweep the servo from 180 to 0 degrees
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servoChannel, 0, pulselen);
    pwm.setPWM(servoChannel2, 0, pulselen);
    pwm.setPWM(servoChannel3, 0, pulselen);
    if (pulselen == 320)
    {
      delay(500);
    }
    delay(10);
  }

  delay(500);
}
