#include "ButtonCross.h"

ButtonCross::ButtonCross(String n, int p, float v1, float v2, float v3, float v4, float v5) 
: SensorBase(p, n) {
	setValues.resize(5);
	setValues[0] = v1;
	setValues[1] = v2;
	setValues[2] = v3;
	setValues[3] = v4;
	setValues[4] = v5;
	
}

void ButtonCross::update() {
	if (millis() - lastTime >= waitTime) {
		press = -1;
		value = analogRead(pin);
		
		for (size_t i = 0; i < 5; i++) {
			if (abs(value - setValues[i]) < tolerance)  {
				press = i; 
				lastTime = millis();
		
			}
		}
	}
	
	
	
}

float ButtonCross::rawData() {
	return value;
}

bool ButtonCross::pressed(int i) {
	if (press == i)
	{
		return true;
	}
	return false;
}
