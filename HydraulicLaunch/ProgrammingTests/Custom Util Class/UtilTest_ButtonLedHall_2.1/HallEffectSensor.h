// HallEffectSensor.h
#ifndef HALLEFFECTSENSOR_H
#define HALLEFFECTSENSOR_H

class HallEffectSensor {
  public:
    HallEffectSensor(int pin);
    int readSensorValue();
  private:
    int sensorPin;
  };

#endif // HALLEFFECTSENSOR_H
