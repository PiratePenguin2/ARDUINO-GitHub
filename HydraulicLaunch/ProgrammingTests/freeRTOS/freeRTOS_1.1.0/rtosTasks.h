#ifndef RTOSTASKS_H
#define RTOSTASKS_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// Function prototypes for tasks
void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

#endif // RTOSTASKS_H
