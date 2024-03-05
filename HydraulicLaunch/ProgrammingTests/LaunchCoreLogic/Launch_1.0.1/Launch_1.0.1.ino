// Launch Main
#include "Motors.cpp"

bool eStopState = true;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);

    // Create instances of different Motor types
    Motor launchBrakeA(Motor::MotorDeg, 8);      // MotorDeg (brake) with pin 8
    Motor launchBrakeB(Motor::MotorDeg, 9);      // MotorDeg (brake) with pin 9
    Motor launchBrakeC(Motor::MotorDeg, 10);     // MotorDeg (brake) with pin 10
    Motor launchBrakeD(Motor::MotorDeg, 11);     // MotorDeg (brake) with pin 11
    Motor launchBrakeE(Motor::MotorDeg, 12);     // MotorDeg (brake) with pin 12

    Motors launchBrakes[] = {
      launchBrakeA,
      launchBrakeB,
      launchBrakeC,
      launchBrakeD,
      launchBrakeE
    };

}

void loop() {
    // Check for launch sequence start
    delay(2000);
    eStopState = false;
    //allMotorsDefault();

    while (true)
    {
      if (true)
      {
        launchSeqStart();
      }
    }
}

void launchSeqStart()
{
  while(!launchBrakes.setState(BRAKES_DOWN)){}  // Wait until the brakes are set as DOWN
  delay(2000);
  while(!launchBrakes.setState(BRAKES_UP  )){}  // Wait until the brakes are set as UP
  delay(2000);
}


/*
    Motor motorDeg(Motor::MotorDeg, 9);      // MotorDeg with pin 9
    Motor motorCont(Motor::MotorCont, 10);   // MotorCont with pin 10
    Motor motorESC(Motor::MotorESC, 11);     // MotorESC with pin 11
    Motor motorDC(Motor::MotorDC, 12);       // MotorDC with pin 12

    motorDeg.setPos(50);                      // Set position for MotorDeg, degrees by default
    motorCont.setSpeed(75);                   // Set continuous speed for MotorCont
    motorESC.setSpeed(100);                   // Set speed for ESC for MotorESC
    motorDC.setPos(2, Motor::Inches);         // Set position for MotorDC to a position in inches
*/
