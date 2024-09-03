#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_PCF8574.h>
#include "PTservo.h"
#include "PTdcmotor.h"
#include "Sensor.h"
#include "Timer.h"

class Blocks {
  public:
    enum BlockState {
      IDLE,
      APPROACHING,
      CENTERING,
      PARKED,
      LEAVING
    };

    Blocks() : currentState(IDLE) {}

    void updateState() {
      switch (currentState) {
        case IDLE:
          // Code for IDLE state
          Serial.println("Block is IDLE");
          break;

        case APPROACHING:
          // Code for APPROACHING state
          Serial.println("Block is APPROACHING");
          break;

        case CENTERING:
          // Code for CENTERING state
          Serial.println("Block is CENTERING");
          break;

        case PARKED:
          // Code for PARKED state
          Serial.println("Block is PARKED");
          break;

        case LEAVING:
          // Code for LEAVING state
          Serial.println("Block is LEAVING");
          break;
      }
    }

    void setState(BlockState newState) {
      currentState = newState;
      this->updateState();
    }

    BlockState getState() {
      return currentState;
    }

  private:
    BlockState currentState;
};



// Create PCA9685 objects for different boards
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);  // PCA9685 at address 0x40
Adafruit_PCF8574 pcf1;

Blocks station;

// Create DCmotor, servo, and sensor objects
PTdcmotor tireA = PTdcmotor(pwm1, 0);
PTdcmotor tireB = PTdcmotor(pwm1, 1);

PTservo servoA  = PTservo(pwm1, 8);
PTservo servoB  = PTservo(pwm1, 9);

Sensor hallA;
Sensor hallB;

Timer sensorTimer = new Timer();

int count = 0;

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

  hallA.attach(4, pcf1);
  hallB.attach(5, pcf1);

  // Start with motors stopped
  tireA.write(0);
  tireB.write(0);
  servoA.write(90); // Set servo to initial position (90 degrees)
  servoB.write(90);
}

void loop() {
  if (hallA.isTripped())
  {
    if (count == 0)
    {
      station.setState(Blocks::APPROACHING);
      count = 4;
      sensorTimer.setTimer(1150);
    }
    count--;
  }
  if (count == 0 || sensorTimer.timerFinished())
  {
    station.setState(Blocks::IDLE);
    count = 0;
  }

  if (station.getState() == 1) //Approaching
  {
    tireA.write(-100);
    tireB.write(-100);
    servoA.write(45); //30
    servoB.write(45);
    //delay(1000);
  }
  else
  {
    tireA.write(0);
    tireB.write(0);
    servoA.write(150);
    servoB.write(150);
  }
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
