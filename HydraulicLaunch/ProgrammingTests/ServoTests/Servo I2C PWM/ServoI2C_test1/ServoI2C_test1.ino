#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600
#define SERVO_FREQ 50

uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   
  pulselength /= SERVO_FREQ;   
  pulselength /= 4096;  
  pulse *= 1000000;  
  pulse /= pulselength;
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  // Set servo to 135 degrees
  pwm.setPWM(servonum, 0, map(30, 0, 180, SERVOMIN, SERVOMAX));
  delay(1000); // Adjust delay as needed
  
  // Set servo back to 45 degrees
  pwm.setPWM(servonum, 0, map(60, 0, 180, SERVOMIN, SERVOMAX));
  delay(1000); // Adjust delay as needed
  
  servonum++;
  if (servonum > 2) servonum = 0; // Testing the first 8 servo channels
}
