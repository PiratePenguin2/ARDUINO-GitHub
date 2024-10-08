#include <Servo.h>

//Servo servoA;
Servo servoD;  // Create a servo object
Servo servoE;

int presetPosition[5][2] = {
  {20, 135},
  {20, 135},
  {20, 135},
  {20, 135},
  {15, 135}
};
int currentServo = 5;

void setup() {
  //servoA.attach(4);
  servoD.attach(10);  // Attach the servo to digital pin 11
  servoE.attach(11);  // Attach the servo to digital pin 12
}

void loop() {
  moveServoToPreset(true);  // Move the servo to the preset position
  delay(2500);  // Wait for 1 second (adjust as needed)
  moveServoToPreset(false);  // Move the servo to the preset position
  delay(2500);  // Wait for 1 second (adjust as needed)
}

void moveServoToPreset(bool dir) {
  //servoA.write(dir ? presetPosition[1-1][0] : presetPosition[1-1][0] + presetPosition[1-1][1]);
  
  servoD.write(dir ? presetPosition[4-1][0] : presetPosition[4-1][0] + presetPosition[4-1][1]);  // Move the servo to the preset position
  servoE.write(dir ? presetPosition[5-1][0] : presetPosition[5-1][0] + presetPosition[5-1][1]);
  delay(500);  // Wait for the servo to reach the position (adjust as needed)
}
