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
      LEAVING,
      APPROACHING,
      THROUGH,
      CENTERING,
      PARKING,
      PARKED
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
    
        case LEAVING:
          // Code for LEAVING state
          Serial.println("Block is LEAVING");
          break;
    
        case THROUGH:
          // Code for THROUGH state
          Serial.println("Block is THROUGH");
          break;
    
        case CENTERING:
          // Code for CENTERING state
          Serial.println("Block is CENTERING");
          break;
    
        case PARKING:
          // Code for PARKING state
          Serial.println("Block is PARKING");
          break;
    
        case PARKED:
          // Code for PARKED state
          Serial.println("Block is PARKED");
          break;
    
        default:
          Serial.println("Unknown state");
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
Adafruit_PCF8574 pcf2;
Adafruit_PCF8574 pcf3;

Blocks station;

// Create DCmotor, servo, and sensor objects
PTdcmotor tire1A = PTdcmotor(pwm1, 0);
PTdcmotor tire1B = PTdcmotor(pwm1, 1);
PTdcmotor tire2A = PTdcmotor(pwm1, 12);

PTservo servo1A  = PTservo(pwm1, 2);
PTservo servo1B  = PTservo(pwm1, 3);
PTservo servo2A  = PTservo(pwm1, 14);

Sensor hallStnA;
Sensor hallStnB;
Sensor hallStnC;
Sensor hallStnD;
Sensor hallStnCntr;

Sensor hallHoldA;
Sensor hallHoldB;
Sensor btnDisp;

Timer sensorTimer;

int count = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize I2C communication and each PCF8574
  Serial.println("\nInitializing PCF8574 Boards");
  initializeBoard(pcf1, 0x20);
  initializeBoard(pcf2, 0x21);
  initializeBoard(pcf3, 0x22);
  Serial.println("All PCF8574 Boards Initiated!\n");

  // Initialize PCA9685 boards
  Serial.println("Initializing PCA9685 Boards");
  initializeBoard(pwm1, 50);  // Initialize PCA9685 at address 0x40
  Serial.println("All PCA9685 Boards Initiated!\n");

  tire1A.initializePins(0, 1, pcf1);
  tire1B.initializePins(2, 3, pcf1);
  tire2A.initializePins(0, 1, pcf3);

  hallStnA.attach(0, pcf2);
  hallStnB.attach(1, pcf2);
  hallStnC.attach(2, pcf2);
  hallStnD.attach(3, pcf2);
  hallStnCntr.attach(4, pcf2);

  hallHoldA.attach(4, pcf3);
  hallHoldB.attach(5, pcf3);
  
  btnDisp.attach(6, pcf3);

  // Start with motors stopped
  tire1A.write(0);
  tire1B.write(0);
  servo1A.write(90); // Set servo to initial position (90 degrees)
  servo1B.write(90);
}

void loop() {
  if (hallHoldA.isTripped())
  {
    station.setState(Blocks::APPROACHING);
    hallStnD.count(0);
    hallStnC.count(0);
    hallStnB.count(0);
    hallStnA.count(0);
    hallStnCntr.count(0);
  }
  
  if (hallStnD.isTripped())
  {
    hallStnD.count();
    if (station.getState() == 2 && hallStnD.getCount() == 1)
    {
      station.setState(Blocks::THROUGH);
      hallStnD.count(0);
      hallStnC.count(0);
      hallStnB.count(0);
      hallStnA.count(0);
      hallStnCntr.count(0);
      //sensorTimer.setTimer(1150);
    }
    if (station.getState() == 1 && hallStnD.getCount() == 3)
    {
      station.setState(Blocks::THROUGH);
      hallStnD.count(0);
      hallStnC.count(0);
      hallStnB.count(0);
      hallStnA.count(0);
      hallStnCntr.count(0);
    }
  }
  
  if (hallStnA.isTripped())
  {
    hallStnA.count();
    if (hallStnA.getCount() == 1)
    {
      sensorTimer.setTimer(1500);
    }
    if (station.getState() == 3 && (hallStnA.getCount() >= 3 || sensorTimer.isFinished())) //THROUGH
    {
      if (sensorTimer.isFinished())
      {
        Serial.println("Used Timer");
      }
      station.setState(Blocks::CENTERING);
      hallStnD.count(0);
      hallStnC.count(0);
      hallStnB.count(0);
      hallStnA.count(0);
      hallStnCntr.count(0);
    }
  }

  if (hallStnB.isTripped())
  {
    hallStnB.count();
    if (station.getState() == 4 && hallStnB.getCount() >= 2) //CENTERING
    {
      station.setState(Blocks::PARKING);
    }
  }

  if (hallStnCntr.isTripped())
  {
    hallStnCntr.count();
    if (station.getState() == 5) //PARKING
    {
      if (hallStnCntr.getCount() == 2)
      {
        station.setState(Blocks::PARKED);
        /*hallStnD.count(0);
        hallStnC.count(0);
        hallStnB.count(0);
        hallStnA.count(0);
        hallStnCntr.count(0);*/
      }
      else if (hallStnCntr.getCount() >= 3)
      {
        
      }
    }
  }

  if (hallHoldB.isTripped() || btnDisp.isUntripped()) //Untripped is temporary
  {
    station.setState(Blocks::LEAVING);
  }


  
  /*if ((count == 0 && station.getState() != 1) || sensorTimer.isFinished())
  {
    station.setState(Blocks::IDLE);
    count = 0;
  }*/
  
  if (station.getState() == 1) //LEAVING
  {
    tire1A.write(50);
    tire1B.write(50);
    servo1A.write(45); //30
    servo1B.write(45);
  }
  else if (station.getState() == 2) //APPROACHING
  {
    tire1A.write(0);
    tire1B.write(0);
    servo1A.write(150); //30
    servo1B.write(150);
  }
  else if (station.getState() == 3) //THROUGH
  {
    tire1A.write(-100);
    tire1B.write(-100);
    servo1A.write(45); //30
    servo1B.write(45);
  }
  else if (station.getState() == 4) //CENTERING
  {
    tire1A.write(0);
    tire1B.write(0);
    servo1A.write(150); //30
    servo1B.write(150);
  }
  else if (station.getState() == 5) //PARKING
  {
    tire1A.write(35);
    tire1B.write(35);
    servo1A.write(45); //30
    servo1B.write(45);
  }
  else if (station.getState() == 6) //PARKED
  {
    tire1A.write(0);
    tire1B.write(0);
    servo1A.write(45); //30
    servo1B.write(45);
  }

  else
  {
    tire1A.write(0);
    tire1B.write(0);
    servo1A.write(150);
    servo1B.write(150);
  }
  
Serial.print(station.getState());
Serial.print(" ");
Serial.print(sensorTimer.getElapsedTime());
Serial.print(" ");
Serial.println(sensorTimer.isFinished());
delay(50);
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
