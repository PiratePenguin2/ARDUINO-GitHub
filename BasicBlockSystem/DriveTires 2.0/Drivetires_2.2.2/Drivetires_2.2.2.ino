#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_PCF8574.h>



// Custom Servo Motor Class
class PTservo {
  // Define the channel for the servo (0-15) 320 mid, +-225
  #define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX  545 // This is the 'maximum' pulse length count (out of 4096)

public:
  PTservo(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

  void write(int angle) {
    // Constrain angle to range 0 to 180
    angle = constrain(angle, 0, 180);

    int pwmValue = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    
    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }
  
private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
};

// Custom DC Motor Class
class PTdcmotor {
public:
  PTdcmotor(Adafruit_PWMServoDriver& driver, uint8_t channel) :
      pwmDriver(driver), pwmChannel(channel) {}

  void initializePins(uint8_t in1, uint8_t in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    usePcf = false;
  }

  void initializePins(uint8_t in1, uint8_t in2, Adafruit_PCF8574& pcf) {
    pin1 = in1;
    pin2 = in2;
    pcfBoard = &pcf;
    pcfBoard->pinMode(pin1, OUTPUT);
    pcfBoard->pinMode(pin2, OUTPUT);
    usePcf = true;
  }

  void write(int speed) {
    // Constrain speed to range -100 to 100
    speed = constrain(speed, -100, 100);

   // Set corresponding IN pins
    if (usePcf) {
      pcfBoard->digitalWrite(pin1, speed > 0 ? HIGH : LOW);
      pcfBoard->digitalWrite(pin2, speed < 0 ? HIGH : LOW);
    } else {
      digitalWrite(pin1, speed > 0 ? HIGH : LOW);
      digitalWrite(pin2, speed < 0 ? HIGH : LOW);
    }
    
    // Map pulse width to PCA9685 PWM range (0-4095)
    int pwmValue = map(abs(speed), 0, 100, 0, 4095);

    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }
  
private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  Adafruit_PCF8574* pcfBoard = nullptr;  // Use a pointer for the PCF8574 instance
  uint8_t pin1;
  uint8_t pin2;
  bool usePcf = false;  // Flag to check whether to use PCF8574 or regular digital pins
};


// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PCF8574 pcf1;
//Adafruit_PCF8574 pcf2;
//Adafruit_PCF8574 pcf3;
//int motorA = 0;

  PTdcmotor tireA = PTdcmotor(pwm, 0);
  PTdcmotor tireB = PTdcmotor(pwm, 1);
  PTservo servoA  = PTservo(pwm, 8);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize I2C communication and each PCF8574
  Serial.println("\nInitializing PCF8574 Boards");
  
  if (!pcf1.begin(0x20)) {
    Serial.println("Couldn't find PCF8574 at address 0x20");
    while (1);
  }
  
  /*if (!pcf2.begin(0x21)) {
    Serial.println("Couldn't find PCF8574 at address 0x21");
    while (1);
  }
  
  if (!pcf3.begin(0x22)) {
    Serial.println("Couldn't find PCF8574 at address 0x22");
    while (1);
  }*/
  Serial.println("All PCF8574 Boards Initiated!\n");

  
  // Initialize PCA9685
  Serial.println("Initializing PCA9685 Boards");
  if (!pwm.begin()) {
    Serial.println("Couldn't find PCA9685 at address 0x40");
    while (1);
  }
  pwm.setPWMFreq(50);
  Serial.println("All PCA9685 Boards Initiated!\n");

  tireA.initializePins(0, 1, pcf1);
  tireB.initializePins(2, 3, pcf1);

  // Start with motors stopped
  tireA.write(0);
  tireB.write(0);
  servoA.write(90); // Set servo to initial position (90 degrees)
}

void loop() {

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
