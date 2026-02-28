#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"

class ButtonCross : public SensorBase {
private:
	int press = -1;
	std::vector<float> setValues;
	float lastTime = 0;
	float waitTime = 20;

	int tolerance = 15;	
public: 	
	ButtonCross(String n, int p, float v1, float v2, float v3, float v4, float v5);
	void update() override;
	float rawData() override;
	bool pressed(int i);
};