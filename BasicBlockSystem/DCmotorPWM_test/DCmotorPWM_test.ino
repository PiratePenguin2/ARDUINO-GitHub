#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Custom DC Motor Class
class DCmotor {
public:
  DCmotor(Adafruit_PWMServoDriver& driver, uint8_t channel, uint8_t in1, uint8_t in2) :
    pwmDriver(driver), pwmChannel(channel), pin1(in1), pin2(in2) {}

  void attach() {
    // Initialize PWM settings
    pwmDriver.setPWMFreq(60); // Set frequency to 60 Hz for DCmotor control
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void write(int speed) {
    // Constrain speed to range -100 to 100
    speed = constrain(speed, -100, 100);

    // Set corresponding IN pins
    speed > 0 ? digitalWrite(pin1, HIGH) : digitalWrite(pin1, LOW);
    speed < 0 ? digitalWrite(pin2, HIGH) : digitalWrite(pin2, LOW);
    
    // Map pulse width to PCA9685 PWM range (0-4095)
    int pwmValue = map(abs(speed), 0, 100, 0, 4095);

    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }
  
private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  uint8_t pin1;
  uint8_t pin2;
};

// PCA9685 PWM channels
const int motorA = 0;  // Channel for Motor 1
const int motorB = 1;  // Channel for Motor 2

DCmotor tireA = DCmotor(pwm, motorA, 2, 3);
DCmotor tireB = DCmotor(pwm, motorB, 4, 5);

void setup() {
  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(1600);  // Set frequency to 1.6 kHz for motor control
  
  // Initialize DCmotors
  tireA.attach();
  tireB.attach();

  // Start with motors stopped
  tireA.write(0);
  tireB.write(0);
}

void loop() {

  tireA.write(100);
  tireB.write(100);

  delay(2000);  // Run forward for 2 seconds

  tireA.write(0);
  tireB.write(0);

  delay(1000);  // Stop for 1 second

  tireA.write(-100);
  tireB.write(-100);

  delay(2000);  // Run backward for 2 seconds

  tireA.write(0);
  tireB.write(0);

  delay(1000);  // Stop for 1 second
}
