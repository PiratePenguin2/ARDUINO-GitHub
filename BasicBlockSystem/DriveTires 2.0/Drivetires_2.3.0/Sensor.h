#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_PCF8574.h>

class Sensor {
  public:
    // Constructors
    Sensor();
    void attach(uint8_t pin);
    void attach(uint8_t pin, Adafruit_PCF8574 &pcf);
    
    // Read functions
    bool read();
    bool isTripped();
    int analogRead();

  private:
    uint8_t _pin;
    Adafruit_PCF8574 *_pcf;
    bool _usingPCF;
    bool storedState;
};

#endif
