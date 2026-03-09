#pragma once
#include <Arduino.h>

class Application;

class Calibration {
private:
	Application* app;

public:
	Calibration(Application* a);

	void calibrateBno();
};