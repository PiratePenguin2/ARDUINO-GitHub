#include "rtosTasks.h"
#include <Servo.h>
#include <PID_v1.h>

// Define your constants or any other global variables here
const int ledPin = 3;  // Move this declaration to tasks.cpp if it's not declared globally
const int servoPin = 4; // Pin for the servo

Servo myServo; // Create a servo object

double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, 0.5, 0.01, 0.1, DIRECT);  // Adjusted PID parameters

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

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Attach the servo to the corresponding pin
  myServo.attach(servoPin);

  // Set the Setpoint (desired position)
  Setpoint = 90.0;

  // Initialize PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 180);

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A7);

    // Map the potentiometer value to the servo range (adjust as needed)
    int servoPosition = map(sensorValue, 0, 1023, 0, 180);
    Input = servoPosition;

    // Compute PID output
    myPID.Compute();

    // Set the servo position based on the PID output
    myServo.write((int)Output); // Ensure Output is cast to an integer

    // Print diagnostic information
    Serial.print("Input: ");
    Serial.print(Input);
    Serial.print("   Output: ");
    Serial.println(Output);

    vTaskDelay(500 / portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
  }
}
