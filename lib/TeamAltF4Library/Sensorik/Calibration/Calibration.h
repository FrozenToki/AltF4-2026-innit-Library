#pragma once
#include <Arduino.h>
#include "Sensorik/SensorManager/SensorManager.h"
#include "Outputs/OutputManager/OutputManger.h"

class Application;

class Calibration {
private:
	Application* app;

	Ssd1306* display;
	ButtonCross* buttonC;

	IrSensor* irL;
	IrSensor* irR;

	IrRing* ring;

public:
	Calibration(Application* a);


	void calibrateIrSensors();

	void calibrateIrRing();
};