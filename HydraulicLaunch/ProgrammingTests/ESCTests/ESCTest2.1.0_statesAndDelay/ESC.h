#pragma once

class Esc {
public:
    Esc();
    void setSpeed(int speed, int escPin);

private:
    int currentSpeed;
};
