#pragma once
#include <Arduino.h>
#include "Outputs/OutputBase/Outputs.h"
#include "config/Config.h"

class Motor : public OutputBase {
private: 
    int pinInA;
    int pinInB;
    int pinPwm;
public: 
    Motor(int inA, int inB, int pwm, String n);
    void turnOn(float speed);
    void turnOff();
};

