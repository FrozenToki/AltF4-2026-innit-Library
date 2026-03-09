#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/IrRing/IrRing.h"
#include "config/Config.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"
#include "Geometry/Geometry.h"
#include "Sensorik/SensorBase/IrSensors/IrSensors.h"
#include <EEPROM.h>
#include "MovingAverage/MovingAverage.h"
#include "Sensorik/SensorManager/SensorManager.h"

class Application;


class States {
private: 
	Application* app;
	
	// === BALL_STATE ===
	IrRing* irRing;
	
	Bno055* bno055;

	IrSensor* irFL;
	IrSensor* irFR;

	int ballInHolderThreshould = 0;

	// === ROBOT_STATE ===
	EZ* ezVL;
	EZ* ezV;
	EZ* ezVR;

	Sr04* distRight;
	Sr04* distBack;
	Sr04* distLeft;

	MovingAverage* movingAverage;

	MovingAverage* vl;
	MovingAverage* v;
	MovingAverage* vr;

 int lastRobotState = 0;	

	
	
public: 
	States(Application* a);
	int ballState();

	int getBallInHolderThreshould();

	void setBallInHolderThreshould(int i);

	int robotState();
};