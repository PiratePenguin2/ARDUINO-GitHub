/*
  IR Sensor Control

  This sketch demonstrates the usage of IRHelper class to interface with infrared (IR) sensors.
  The IRHelper class provides functions to read sensor values, adjust thresholds, distances,
  and tolerances, and check if the sensor readings meet certain criteria.

  Functions:
  - sensorRead(): Reads the sensor value from the connected analog pin.
  - sensorFlagged(): Checks if the sensor reading is above the threshold.
  - adjustThreshold(int thresh): Adjusts the threshold value for sensor readings.
  - adjustDistance(int dist): Adjusts the exact distance away from the sensor.
  - adjustTolerance(int tol): Adjusts the tolerance range around the exact distance.
  - distanceMet(int tol): Checks if the sensor reading falls within the specified tolerance range around the exact distance.
  - distanceMet(): Checks if the sensor reading falls within the default tolerance range around the exact distance.
  - getThreshold(): Retrieves the current threshold value.
  - getDistance(): Retrieves the current exact distance value.
  - getTolerance(): Retrieves the current tolerance value.

  Created by PiraTechnics, 4/12/2024
*/

#include "IRHelper.h"

// Create an instance of every IR sensor needed
IRHelper sensor1(A0, 75, 120, 30); //IRsensor pin, threshold distance for high/low, exact distance away, +- tolerance for exact distance away
IRHelper sensor2(A1);               //Defaults are 100 threshold, 150 distance, 25 tolerance
IRHelper sensor3(A2, 50);
IRHelper sensor4(A3, 50, 173); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Print sensor value, threshold, distance, tolerance, flag status, and distance met status
  Serial.print("Sensor value: ");
  Serial.println(sensor1.sensorRead()); // Return sensor value (already built in to sensorFlagged() and distanceMet() functions)
  Serial.print("Threshold: ");
  Serial.println(sensor1.getThreshold());
  Serial.print("Distance: ");
  Serial.println(sensor1.getDistance());
  Serial.print("Tolerance: ");
  Serial.println(sensor1.getTolerance());
  Serial.print("Flagged: ");
  Serial.println(sensor1.sensorFlagged()); // Read sensor and check if it's flagged (above the threshold)
  Serial.print("Distance met: ");
  Serial.println(sensor1.distanceMet()); // Read sensor and check if the distance is right, or within the tolerance
  Serial.println("");
  
  delay(250);
}
