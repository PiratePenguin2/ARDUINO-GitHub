// Launch Main
#include "Motor.h"

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);

    // Create instances of different Motor types
    Motor motorDeg(Motor::MotorDeg, 9);      // MotorDeg with pin 9
    Motor motorCont(Motor::MotorCont, 10);   // MotorCont with pin 10
    Motor motorESC(Motor::MotorESC, 11);     // MotorESC with pin 11
    Motor motorDC(Motor::MotorDC, 12);       // MotorDC with pin 12

    // Call functions based on motor type
    motorDeg.setPos(50);                      // Set position for MotorDeg, degrees by default
    motorCont.setSpeed(75);                   // Set continuous speed for MotorCont
    motorESC.setSpeed(100);                   // Set speed for ESC for MotorESC
    motorDC.setPos(2, Motor::Inches);         // Set position for MotorDC to a position in inches

    delay(1000);
    motorDC.setPos(15, Motor::Percent);       // Set position for MotorDC to a position in percent of its range of motion
}

void loop() {
    // Your main loop code here
}
