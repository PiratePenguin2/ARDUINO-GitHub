#include <Arduino_FreeRTOS.h>
#include <Servo.h>

Servo servoMotor;

// Task handles
TaskHandle_t servoTaskHandle = NULL;

// Servo rotation task parameters
const TickType_t servoTaskDelay = pdMS_TO_TICKS(100); // Task delay in milliseconds

// Servo rotation task function
void servoRotationTask(void *pvParameters) {
  int targetPosition = *((int *)pvParameters);
  const int maxSpeed = 5; // Maximum speed of the servo (degrees per step)
  const int delayTime = 15; // Delay between steps (in milliseconds)

  // Move the servo to the target position with variable speed
  int currentPosition = servoMotor.read();
  int direction = (targetPosition - currentPosition > 0) ? 1 : -1;
  int speed = min(abs(targetPosition - currentPosition), maxSpeed);

  for (int pos = currentPosition; pos != targetPosition; pos += direction * speed) {
    servoMotor.write(pos);
    vTaskDelay(pdMS_TO_TICKS(delayTime));
  }

  vTaskDelete(NULL);
}

void setup() {
  // Initialize serial communication for debugging purposes
  Serial.begin(9600);

  // Attach servo motor to pin 9
  servoMotor.attach(9);

  // Create servo rotation task with priority 1
  int targetPosition = 90; // Set your target position here
  xTaskCreate(servoRotationTask, "ServoRotation", 128, &targetPosition, 1, &servoTaskHandle);

  // Other initialization code here
}

void loop() {
  // Your main code here
}
