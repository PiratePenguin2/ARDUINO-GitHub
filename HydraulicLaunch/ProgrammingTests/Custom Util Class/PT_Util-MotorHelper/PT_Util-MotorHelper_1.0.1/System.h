// System.h
#pragma once

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

class System {
private:
    String boardName;
    
public:
    System(String name) : boardName(name) {}

    void begin() {
        xTaskCreate(blinkTask, "BlinkTask", 128, NULL, 1, &blinkTaskHandle);
    }

    void print(String text) {
      Serial.println(boardName + ":\t" + text);
    }

private:
    static TaskHandle_t blinkTaskHandle;
    static void blinkTask(void *pvParameters) {
        (void) pvParameters;
        int blinkDelay = 500;

        pinMode(LED_BUILTIN, OUTPUT);

        while (true) {
            digitalWrite(LED_BUILTIN, HIGH);   // Turn on the LED
            vTaskDelay(pdMS_TO_TICKS(blinkDelay));   // Delay for 1000ms
            digitalWrite(LED_BUILTIN, LOW);    // Turn off the LED
            vTaskDelay(pdMS_TO_TICKS(blinkDelay));   // Delay for 1000ms
        }
    }
};

TaskHandle_t System::blinkTaskHandle = NULL;
