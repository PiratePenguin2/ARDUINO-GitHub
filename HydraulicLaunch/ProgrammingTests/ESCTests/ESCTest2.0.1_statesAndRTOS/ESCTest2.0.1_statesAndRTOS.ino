#include <Arduino_FreeRTOS.h>

// Main.cpp
#include <FreeRTOS.h>
#include "LAUNCH.cpp"

LAUNCH launch;

void launchTask(void *pvParameters) {
    for (;;) {
        launch.update();
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Adjust the delay as needed
    }
}

void setup() {
    Serial.begin(9600);
    launch.initialize();
    launch.startLaunchSequence();  // Initial state change to LAUNCHREADY

    // Create FreeRTOS task for launch updates
    xTaskCreate(launchTask, "LaunchTask", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}

void loop() {
    // This should never be reached due to the FreeRTOS scheduler
    // Keep it empty or add non-blocking code if necessary
}
