#pragma once
#include <Arduino.h>
#include "Outputs/OutputBase/Outputs.h"
#include "config/Config.h"

class Motor : public OutputBase {
private: 
    int pinInA;
    int pinInB;
    int pinPwm;
		int pinAmp;
		float amperUsage = 0;
		bool turnD;
public: 
    Motor(int inA, int inB, int pwm, int amp, String n, bool turnDirection = true);
    void turnOn(float speed);
    void turnOff();
		void updateAmperUsage();
		float getAmperUsage();
};

