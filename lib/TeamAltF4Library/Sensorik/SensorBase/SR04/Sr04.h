#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"



class Sr04 : public SensorBase {
	private: 
		int pinTrig;
		int pinEcho;
	public:
		Sr04(int pinT, int pinE, String n);
		void update() override;
		float rawData() override;
		
};