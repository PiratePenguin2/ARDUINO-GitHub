#include "rtosTasks.h"

// Define your constants or any other global variables here

const int ledPin = 3;  // Move this declaration to tasks.cpp if it's not declared globally

// TaskBlink implementation
void TaskBlink(void *pvParameters)
{
  (void)pvParameters;

  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);

  for (;;)
  {
    digitalWrite(ledPin, HIGH);                   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1000 / portTICK_PERIOD_MS);        // wait for one second
    digitalWrite(ledPin, LOW);                    // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS);        // wait for one second
  }
}


// TaskAnalogRead implementation
void TaskAnalogRead(void *pvParameters)
{
  (void)pvParameters;

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A7);
    
    // print out the value you read:
    Serial.print("Potentiometer Value: ");  // Move the cursor back to the beginning of the line using '\r'
    Serial.println(sensorValue);
    
    vTaskDelay(500 / portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
  }
}
