#pragma once
#include "Arduino.h"
#include "Outputs/OutputBase/Motor/Motor.h"


class Application;


class DrivingControl {
private:
    Motor* frontLeft;
    Motor* back;
    Motor* frontRight;
    Application* app;
public:
    DrivingControl(Application* a);   
    void drive(float angle, float motorSpeed, float rotation);
    void addMotor(int index, Motor* motor);
    


};

