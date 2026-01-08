#pragma once
#include <Arduino.h>
#include "Outputs/OutputBase/Outputs.h"

class Led : public OutputBase {
private:
	int pin;
	int brightness;
	
public:
	Led (int p, String n);
		
	void turnOn(int brightnessValue = -1);
	void turnOff() const;
	
	void setLedBrightness(int brightnessValue);
	int getLedBrightness() const;
};






