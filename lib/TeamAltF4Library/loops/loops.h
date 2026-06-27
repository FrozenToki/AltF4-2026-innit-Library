#pragma once
#include <Arduino.h>
#include "Sensorik/SensorManager/SensorManager.h"
#include "Config/Config.h"

class ApplicationInnit;

class Loops {
	public: 
		Loops(ApplicationInnit* a);
		void readDistance();

	private:
		ApplicationInnit* app;
		
		Sr04* distRight;
		Sr04* distBack;
		Sr04* distLeft;

		EZ* ezVL;
		EZ* ezV;
		EZ* ezVR;

		int status = 0;
		unsigned long time = 0;

};