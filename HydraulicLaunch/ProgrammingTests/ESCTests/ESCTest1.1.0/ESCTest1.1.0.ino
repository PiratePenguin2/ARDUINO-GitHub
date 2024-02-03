/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/
// Main, ESCTest1.0.0

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "ESC.h"

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int escPin = 12;    // the number of the escPin pin
//const int framerate = 20;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status


SemaphoreHandle_t motorSemaphore; // Semaphore to protect the motor object

ESC motor(escPin);  // Create an ESC object to control the ESC




void setup() {
  Serial.begin(9600);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Attach the ESC on pin escPin
  motor.attach();


  // Create a semaphore to protect the motor object
  motorSemaphore = xSemaphoreCreateMutex();

 // Check if the semaphore was created successfully
  if (motorSemaphore != NULL) {
    // Create and start Task 1 with a 1-second delay
    xTaskCreate(taskFunction1s, "Task1", 1000, NULL, 1, NULL);

    // Create and start Task 2 with a 3-second delay
    xTaskCreate(taskFunction3s, "Task2", 1000, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

  } else {
    // Semaphore creation failed, handle the error
    Serial.println("Error: Failed to create semaphore");
  }
  
}




void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);  // Add this line for debugging

  // Acquire the semaphore before accessing the motor object
  if (xSemaphoreTake(motorSemaphore, portMAX_DELAY) == pdTRUE)
  {  
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
      // turn ESC on:
      motor.newTarget(200);
      
      // Release the semaphore after setting the target speed
      xSemaphoreGive(motorSemaphore);
      vTaskDelay(1000 / portTICK_PERIOD_MS);

      // Acquire the semaphore before updating the speed
      if (xSemaphoreTake(motorSemaphore, portMAX_DELAY) == pdTRUE)
      {
        motor.updateSpeed(1); // speedSmoothing: 0 is infinite, 1 is instant
        xSemaphoreGive(motorSemaphore); // Release the semaphore after updating the speed
      }

    }
    else
    {
      // turn ESC off:
      motor.newTarget(0);

      xSemaphoreGive(motorSemaphore); // Release the semaphore after updating the speed
    }
  }

  // Release the semaphore after accessing the motor object
  xSemaphoreGive(motorSemaphore);
  
  motor.updateSpeed(1); //speedSmoothing: 0 is infinate, 1 is instant
}




void taskFunction1s(void *pvParameters) {
  for (;;) {
    // Task logic goes here
    vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1000 milliseconds
  }
}
void taskFunction3s(void *pvParameters) {
  for (;;) {
    // Task logic goes here
    vTaskDelay(pdMS_TO_TICKS(3000));  // Delay for 3000 milliseconds
  }
}
