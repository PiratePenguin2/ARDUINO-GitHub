#include "PtSensors.h"
#include <iostream>

// Sensor Class Implementation
Sensor::Sensor(int pin, const std::string& name) : pin(pin), name(name), state(false) {}

void Sensor::update() {
    // Simulate state change (e.g., from a digital pin read)
    state = !state; // Toggle state for demonstration purposes
}

bool Sensor::getState() const {
    return state;
}

std::string Sensor::getName() const {
    return name;
}

// Sensors Class Implementation
void Sensors::addCollection() {
    collections.emplace_back();       // Add a new empty collection
    states.emplace_back();            // Add a new empty state vector
}

void Sensors::addSensorToCollection(size_t collectionIndex, int pin, const std::string& name) {
    if (collectionIndex >= collections.size()) {
        std::cerr << "Error: Collection index out of bounds!" << std::endl;
        return;
    }
    collections[collectionIndex].emplace_back(pin, name);
    states[collectionIndex].emplace_back(false); // Add a default state to the cache
}

void Sensors::updateAll() {
    for (size_t i = 0; i < collections.size(); ++i) {
        for (size_t j = 0; j < collections[i].size(); ++j) {
            collections[i][j].update();                  // Update each sensor
            states[i][j] = collections[i][j].getState(); // Cache the updated state
        }
    }
}

std::vector<std::vector<bool>> Sensors::getStates() const {
    return states; // Return the cached states
}

bool Sensors::getSensorState(size_t collectionIndex, size_t sensorIndex) const {
    if (collectionIndex >= states.size() || sensorIndex >= states[collectionIndex].size()) {
        std::cerr << "Error: Sensor index out of bounds!" << std::endl;
        return false;
    }
    return states[collectionIndex][sensorIndex];
}

const Sensor& Sensors::getSensor(size_t collectionIndex, size_t sensorIndex) const {
    return collections.at(collectionIndex).at(sensorIndex);
}
