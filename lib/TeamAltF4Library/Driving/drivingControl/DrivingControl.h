#pragma once
#include "Arduino.h"
#include "Outputs/OutputBase/Motor/Motor.h"
#include "Sensorik/SensorBase/IrRing/IrRing.h"
#include <EEPROM.h>

class Application;


class DrivingControl {
private:
    Motor* frontLeft;
    Motor* back;
    Motor* frontRight;
    Application* app;

		IrRing* ring;

		float ampFactor = 1;

		float distanceThreshold = 0;
public:
    DrivingControl(Application* a);   
    void drive(float angle, float motorSpeed, float rotation);
    void addMotor(int index, Motor* motor);
    void turnOff();

		void setDistanceThreshold(float dist);
		

		float getAmpFactor();
};

