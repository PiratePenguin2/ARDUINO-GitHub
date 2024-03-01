/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/
// Main, ESCTest1.0.0

#include "ESC.h"

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int escPin = 12;    // the number of the escPin pin
const int fps = 20;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
bool buttonPushed = false;
int count = 0;

ESC motor(escPin);  // Create an ESC object to control the ESC


void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Attach the ESC on pin escPin
  motor.attach(); 

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);  // Add this line for debugging

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonPushed)
  {
    count += 1000/fps;
  }
  if (buttonState == HIGH)
  {
    buttonPushed = true;
    count = 0;
  }
  
  if (count < 250)
  {
    // turn ESC on:
    motor.newTarget(200);
  }
  else
  {
    buttonPushed = false;
    // turn ESC off:
    motor.newTarget(0);
  }
  
  motor.updateSpeed(1); //speedSmoothing: 0 is infinate, 1 is instant
  delay(1000/fps);
}