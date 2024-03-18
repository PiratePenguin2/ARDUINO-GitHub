//PT_Util-MotorHelperRunner
#include "PT_Util_MotorHelper.h" // Include the header file where the Motor class and its subclasses are defined

// Create an instance of ServoRot class
ServoPos servoA(9); // Creates a rotate servo conntected to pin 9
ServoPos servoB(10); // Creates a rotate servo conntected to pin 9

void setup() {
    // Initialization code here
    Serial.begin(9600);

    // Move the servo motor to a specific position
    int targetPositionA = 90;
    int speedA = 2; // Adjust speed as needed
    int speedB = 4;
    servoA.move(targetPositionA, speedA);
    servoB.move(targetPositionA);
}

void loop() {
    // Main code here
}
