#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SR04/Sr04.h"
#include "Config/Config.h"

class Application;

class Loops {
	public: 
		Loops(Application* a);
		void readDistance();

	private:
		Application* app;
		Sr04* distRight;
		Sr04* distBack;
		Sr04* distLeft;

		int status = 0;
		unsigned long time = 0;

};