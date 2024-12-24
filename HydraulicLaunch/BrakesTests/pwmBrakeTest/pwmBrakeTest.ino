#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "PTservo.h"
//#include "Timer.h"
#include "Sensor.h"
//#include <vector>
//#include <string>
//#include <map>
using namespace std;


Adafruit_PWMServoDriver brakePWM = Adafruit_PWMServoDriver(0x40);  // PCA9685 at address 0x40

PTservo servo0  = PTservo(brakePWM, 0);
PTservo servo1  = PTservo(brakePWM, 1);
PTservo servo2  = PTservo(brakePWM, 2);
PTservo servo3  = PTservo(brakePWM, 3);
PTservo servo4  = PTservo(brakePWM, 4);

Sensor brakesToggle = Sensor();

// Function to initialize PCA9685 boards with frequency and address
void initializeBoard(Adafruit_PWMServoDriver &pwmBoard, int freq) {
  pwmBoard.begin();
  pwmBoard.setPWMFreq(freq);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Initialized");

  brakesToggle.attach(2);
  Serial.println("BrakesToggle Button Attached");

  initializeBoard(brakePWM, 50);  // Initialize PCA9685 at address 0x40
  Serial.println("PWM Board Initialized");
}


void loop() {
  brakesToggle.update();
  //Serial.println(brakesToggle.read());
  

  if (brakesToggle.read()) {
    servosPos(150);
  }
  else {
    servosPos(20);
  }
  delay(50);
}

void servosPos(int pos) {
  servo0.write(pos);
  servo1.write(pos);
  servo2.write(pos);
  servo3.write(pos);
  servo4.write(pos);
}



