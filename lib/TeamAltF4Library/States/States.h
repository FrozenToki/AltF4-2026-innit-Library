#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/IrRing/IrRing.h"
#include "config/Config.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"
#include "Geometry/Geometry.h"
#include "Sensorik/SensorBase/IrSensors/IrSensors.h"
#include <EEPROM.h>

class Application;


class States {
private: 
	Application* app;
	IrRing* irRing;
	Bno055* bno055;
	IrSensor* irFL;
	IrSensor* irFR;

	int ballInHolderThreshould = 0;
	
public: 
	States(Application* a);
	int ballState();

	int getBallInHolderThreshould();

	void setBallInHolderThreshould(int i);
};