/*
     Controlling multiple servo motors with Arduino
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
#include "LED.h"

LED led1(13);
//LED led2(3);

int sensor = 5; //sensor pin
int val; //numeric variable

int degRight = 180;
int degMid = 90;
int degLeft = 0;

int contMid = 95;
int contRight = contMid + 10;
int contLeft = contMid - 10;

/*Servo servoContA;
Servo servoDegD;
Servo servoDegC;
//Servo servo4;
//Servo servo5;*/

void setup() {
  Serial.begin(9600);

  pinMode(sensor, INPUT); //set sensor pin as input
  
  /*servoContA.attach(5);
  servoDegD.attach(6);
  servoDegC.attach(7);
  //servo4.attach(11);
  //servo5.attach(12);

  moveServos(degMid, contMid);
  delay(2000);*/

}

void loop()
{
  val = digitalRead(sensor); //Read the sensor
  if (val == HIGH) //when magnetic field is detected, turn led on
  {
    ledON();
  }
  else
  {
    ledOFF();
  }
  delay(100);
  
  /*
  moveServos(degRight, contRight);  //180
  ledON();
  delay(2000);

  moveServos(degMid, contMid);  //90
  ledOFF();
  delay(2000);

  moveServos(degLeft, contLeft);  //0
  ledON();
  delay(2000);

  moveServos(degMid, contMid);  //90
  ledOFF();
  delay(2000);
  */
}


/*void moveServos(int pos, int cont)
{
  // move all servos to pos
  servoContA.write(cont);
  servoDegD.write(pos);
  servoDegC.write(pos);
  //servo4.write(0);
  //servo5.write(0);
}*/



void ledON()
{
  led1.turnON();
  //led2.turnON();
  Serial.print("LED 1 state: ");
  Serial.println(led1.getState());
  //Serial.print("LED 2 state: ");
  //Serial.println(led2.getState());
}

void ledOFF()
{
  led1.turnOFF();
  //led2.turnOFF();
  Serial.print("LED 1 state: ");
  Serial.println(led1.getState());
  //Serial.print("LED 2 state: ");
  //Serial.println(led2.getState());
}
