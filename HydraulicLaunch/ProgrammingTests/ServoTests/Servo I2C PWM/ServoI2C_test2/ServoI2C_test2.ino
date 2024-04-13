#include <Wire.h>
#include "ServoHelper.h"

// Define individual servos
ServoHelper brakeF(1);
ServoHelper brakeG(2);

// Define group variables

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  // Initialize individual servos
  brakeF.begin();
  brakeG.begin();
}

void loop() {
  // Set angle for serv
  brakeF.setAngle(30);
  delay(1000); // Adjust delay as needed
  
  // Set angle for all servos in the stationBrakes group
  brakeF.setAngle(60);
  delay(1000); // Adjust delay as needed
}
