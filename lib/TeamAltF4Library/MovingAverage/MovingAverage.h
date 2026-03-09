#pragma once 
#include <Arduino.h>
#include <vector>

class MovingAverage {
private:
	std::vector<float> values;
	
	bool angleMode;
public: 
	MovingAverage(int averageValueCount, bool useAngleMode = false);
	void newValue(float v);
	float getAverage();
};
