#ifndef PTSENSORS_H
#define PTSENSORS_H

#include <vector>
#include <string>

class Sensor {
public:
    Sensor(int pin, const std::string& name);
    void update();              // Update the sensor's state
    bool getState() const;      // Get the current state
    std::string getName() const;

private:
    int pin;
    std::string name;
    bool state;                 // Current state of the sensor (example: true/false)
};

class Sensors {
public:
    void newCollection();                                     // Add a new collection
    void newSensor(size_t collectionIndex, int pin, const std::string& name);
    void updateAll();                                         // Update all sensors and cache their states
    std::vector<std::vector<bool>> getStates() const;         // Get the cached states of all sensors
    bool getSensorState(size_t collectionIndex, size_t sensorIndex) const; // Get an individual sensor's state
    const Sensor& getSensor(size_t collectionIndex, size_t sensorIndex) const;

private:
    std::vector<std::vector<Sensor>> collections;             // Vector of sensor collections
    std::vector<std::vector<bool>> states;                    // Cached states of all sensors
};

#endif
