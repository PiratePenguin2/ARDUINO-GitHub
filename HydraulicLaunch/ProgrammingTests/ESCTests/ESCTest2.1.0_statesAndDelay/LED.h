#pragma once

class Led {
public:
    Led();
    void turnOn();
    void turnOff();
    void blink(int onTime, int offTime);

private:
    bool isOn;
};
