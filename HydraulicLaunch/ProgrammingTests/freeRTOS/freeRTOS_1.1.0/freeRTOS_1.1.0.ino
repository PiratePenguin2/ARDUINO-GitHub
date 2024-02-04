//freeRTOS_1.0.0
#include <Arduino_FreeRTOS.h>
#include "rtosTasks.h"

// define two tasks for Blink and AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

 
// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Now set up two tasks to run independently.
  xTaskCreate(TaskBlink     , "Blink"     , 128,  NULL, 2,  NULL);
  xTaskCreate(TaskAnalogRead, "AnalogRead", 128,  NULL, 1,  NULL);
  
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
 
void loop()
{
// Empty. Things are done in Tasks. Never Block or delay.
}



/*xTaskCreate(
TaskBlink
, "Blink" // A name just for humans
, 128      // This stack size can be checked and adjusted by reading the Stack Highwater
, NULL
, 2        // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
, NULL );*/
