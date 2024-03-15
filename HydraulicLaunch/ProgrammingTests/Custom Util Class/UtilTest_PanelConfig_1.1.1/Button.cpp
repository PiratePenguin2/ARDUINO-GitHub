// Button.cpp
#include "Button.h"
#include "Timer.h"
#include <Arduino.h>
#include <ArrayList.h>






EStopButton::EStopButton() {
  pinNO = 2;
  pinNC = 3;
  pinLED = 4;
  localModes = ArrayList<ButtonMode>();
  localModes.add(OFF);
}

void EStopButton::createEStopButton()
{
  EStopButton button1 = EStopButton();
}

void EStopButton::update()
{
  EStopButton::updateButtonState();
  EStopButton::updateLocalStates();
  EStopButton::updateLampState();
}

void EStopButton::updateButtonState()
{
  prevButtonState = buttonState;
  
  bool readNO = (digitalRead(pinNO) == HIGH);
  bool readNC = (digitalRead(pinNC) == HIGH);
  
  if (readNO && !readNC)
  {
    buttonState = PRESSED;
  }
  else if (!readNO && readNC)
  {
    buttonState = OPEN;
  }
  else if (readNO && readNC)
  {
    buttonState = BOTH; // Will trigger a major unrecoverable fault
  }
  else
  {
    buttonState = NEITHER;  //Would suggest that a wire has come undone
  }
}

void EStopButton::updateLocalStates()
{
  switch (buttonState) {
  case PRESSED:
    this->addMode(TRIPPED);
    this->removeMode(RESET_REQUEST);
    this->removeMode(OPERATING);
    break;
    
  case OPEN:
    if (prevButtonState == PRESSED)
    {
      this->addMode(RESET_REQUEST);
      this->removeMode(TRIPPED);
      this->removeMode(OPERATING);
    }
    this->addMode(TRIPPED);
    break;
    
  case NEITHER:
    if (prevButtonState != NEITHER) //Allow 1000 msec for the state to change away from NEITHER
    {
      timeBtnNeither.setTimer(1000);
    }
    if (timeBtnNeither.timerFinished())
    {
      TRIPPED;
      Serial.println("Check Button wiring");
    }
    break;
    
  case BOTH:
    Serial.print("Unrecoverable fault, crossed wires");
    break;
    
  default:
    Serial.print("Unknown Button State: ");
    Serial.println(buttonState);
    break;
  };
}

void EStopButton::addMode(ButtonMode mode)
{
  for (int i = 1; i < localModes.size(); i++)
  {
    if (mode > localModes.get(i)) // Insert the mode into the list according to the predefined higharchy
    {
      localModes.add(mode);
      break;
    }
  }
}

void EStopButton::removeMode(ButtonMode mode)
{
  localModes.removeItem(mode);
}

void EStopButton::updateLampState()
{
  
}


/*public void EStopButton::createEStopButton(String name, int pinNO)
{
  this.name = name;
  this.pinNO = pinNO;
  this.pinNC = -1;
  this.pinLED = -1;
}

public void EStopButton::createEStopButton(String name, int pinNO, int pinNC)
{
  this.name = name;
  this.pinNO = pinNO;
  this.pinNC = pinNC;
  this.pinLED = -1;
}

public void EStopButton::createEStopButtonLED(String name, int pinNO, int pinNC, int pinLED)
{
  Button name = new Button();
  this.title = "";
  this.pinNO = pinNO;
  this.pinNC = pinNC;
  this.pinLED = pinLED;
}*/
