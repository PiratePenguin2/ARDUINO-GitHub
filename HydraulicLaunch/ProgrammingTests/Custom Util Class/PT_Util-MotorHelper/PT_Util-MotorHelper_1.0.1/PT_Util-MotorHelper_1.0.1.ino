//PT_Util-MotorHelperRunner
#include "System.h"
#include "PT_Util_MotorHelper3.h"
#include "Servo.h"

System miniC("Mini_C");

//ServoPos servoF(10);
//ServoPos servoG(11);
Servo servoF;

void setup() {
    // Initialization code here
    Serial.begin(9600);

    miniC.begin();
    miniC.print("System Started!");

    servoF.attach(10);
    
    servoF.write(90);

}

void loop() {
  /*miniC.print("A");
  servoF.move(90);
    //delay(500);
  miniC.print("B");
  servoF.move(90);
    //delay(500);*/
}
/*
//PT_Util-MotorHelperRunner
#include "System.h"
//#include "PT_Util_MotorHelper3.h"

System miniA("Mini_C");

//ServoPos servoF(10);
//ServoPos servoG(11);

void setup() {
    // Initialization code here
    Serial.begin(9600);

    miniA.begin();
    miniA.print("System Started!");
}

void loop() {
  //servoF.move(45);
  //servoG.move(45);
  delay(2000);
  //servoF.move(135);
  //servoG.move(135);
  delay(2000);
}*/
