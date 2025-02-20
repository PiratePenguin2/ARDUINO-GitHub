#include "PtSensors.h"
#include <iostream>

int main() {
    Sensors sensors;

    // Add collections
    sensors.newCollection("Buttons"); // Collection 0
    sensors.newCollection("HallEffect"); // Collection 1

    // Add sensors to collections
    sensors.newSensor(0, 5, "Temperature");
    sensors.newSensor(0, 6, "Humidity");
    sensors.newSensor(0, 7, "Light");
    sensors.newSensor(0, 8, "Pressure");

    // Batch update all sensors
    sensors.updateAll();

    // Fetch and display all states (batch access)
    auto allStates = sensors.getStates();
    std::cout << "Batch States:\n";
    for (size_t i = 0; i < allStates.size(); ++i) {
        std::cout << "Collection " << i << ": ";
        for (bool state : allStates[i]) {
            std::cout << state << " ";
        }
        std::cout << "\n";
    }

    // Access individual sensor state
    std::cout << "Individual Sensor State:\n";
    std::cout << "Sensor " << sensors.getSensor(0, 1).getName() << " in Collection 0 has state: "
              << sensors.getSensorState(0, 1) << "\n";

    return 0;
}
