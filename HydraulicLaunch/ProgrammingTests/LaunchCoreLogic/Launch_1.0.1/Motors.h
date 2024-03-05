// Motors.h
#pragma once

class Motor {
public:
    // Enum to represent different Motor types
    enum MotorType {
        MotorDeg,
        MotorCont,
        MotorDC,
        MotorESC
    };

    // Enum to represent units for MotorDC
    enum MotorPosUnits {
        Degrees,
        Inches,
        Percent
    };

    // Constructor to initialize the Motor instance with type and pin
    Motor(MotorType type, int p);

    // Function to set the speed (for MotorCont, MotorDC, and MotorESC)
    void setSpeed(int speed);

    // Function to set the speed (for MotorCont, MotorDC, and MotorESC)
    //void setSpeed(int state);

    // Function to set the Motor position (for MotorDeg)
    void setPos(int position);

    // Function to set the position for MotorCont, MotorDC, or MotorESC, specify units (Degrees, Inches, Percent)
    void setPos(float value, MotorPosUnits units);

    // Function to set the position (based on the state) for MotorCont, MotorDC, or MotorESC, specify units (Degrees, Inches, Percent)
    void setPos(int state, MotorPosUnits units);

private:
    int pin;
    MotorType motorType;
    int pos;    // store the last set motor position
    int speed;  // store the last set motor speed
    int state;  // store the last set switch-case state to set a motor to a speed or position
};
