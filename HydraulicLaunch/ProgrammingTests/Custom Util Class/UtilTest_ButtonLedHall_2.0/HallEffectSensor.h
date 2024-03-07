class HallEffectSensor {
  public:
    HallEffectSensor(int pin);
    int readSensorValue();
  private:
    int sensorPin;
  };
