#include <Arduino.h>
#include "IRHelper.h"

// Initialize static member variables
int IRHelper::sensorPin;
int IRHelper::threshold;
int IRHelper::distance;
int IRHelper::tolerance;

IRHelper::IRHelper(int pin, int thresh, int dist, int tol)
{
  sensorPin = pin;
  threshold = thresh;
  distance = dist;
  tolerance = tol;
}

IRHelper::IRHelper(int pin, int thresh, int dist)
{
  sensorPin = pin;
  threshold = thresh;
  distance = dist;
  tolerance = 25; // Default tolerance value
}

IRHelper::IRHelper(int pin, int thresh)
{
  sensorPin = pin;
  threshold = thresh;
  distance = 150; // Default distance value
  tolerance = 25; // Default tolerance value
}

IRHelper::IRHelper(int pin)
{
  sensorPin = pin;
  threshold = 100; // Default threshold value
  distance = 150; // Default distance value
  tolerance = 25; // Default tolerance value
}

int IRHelper::sensorRead()
{
  return analogRead(sensorPin);
}

bool IRHelper::sensorFlagged()
{
  return sensorRead() >= threshold;
}

void IRHelper::adjustThreshold(int thresh)
{
  threshold = thresh;
}

void IRHelper::adjustDistance(int dist)
{
  distance = dist;
}

void IRHelper::adjustTolerance(int tol)
{
  tolerance = tol;
}

bool IRHelper::distanceMet(int tol)
{
  int currentRead = sensorRead();
  return ((currentRead <= distance + tol) && (currentRead >= distance - tol));
}

bool IRHelper::distanceMet()
{
  int currentRead = sensorRead();
  return ((currentRead <= distance + tolerance) && (currentRead >= distance - tolerance));
}

int IRHelper::getThreshold() {
  return threshold;
}

int IRHelper::getDistance() {
  return distance;
}

int IRHelper::getTolerance() {
  return tolerance;
}
