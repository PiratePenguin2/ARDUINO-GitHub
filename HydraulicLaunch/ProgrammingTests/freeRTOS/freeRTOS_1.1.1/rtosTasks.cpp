#include "rtosTasks.h"
#include <Servo.h>

const int ledPin = 3;  // Move this declaration to tasks.cpp if it's not declared globally
const int servoPin = 4; // Pin for the servo

Servo myServo; // Create a servo object

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
  
  myServo.attach(servoPin); // Attach the servo to the corresponding pin

  int lastPos = -1;

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = (int)(analogRead(A7) / 10) * 10;  //Rounded to reduce potentiometer jitter
  
    // Map the potentiometer value to the servo range (adjust as needed)
    int servoPosition = map(sensorValue, 0+200, 1023-200, 0, 180);
  
    if (lastPos != sensorValue)
    {
      myServo.write(servoPosition);// Set the servo position based on the mapped value
      lastPos = sensorValue;
    }
       
    vTaskDelay(100 / portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
  }
}
