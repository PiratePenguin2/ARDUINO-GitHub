#pragma once

class Led {
public:
    Led();
    void turnOn(int ledPin);
    void turnOff(int ledPin);
    void blink(int ledPin, int onTime, int offTime);

private:
    bool isOn;
};
