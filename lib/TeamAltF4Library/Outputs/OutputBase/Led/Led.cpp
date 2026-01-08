#include "Led.h"

Led::Led(int p, String n) : OutputBase(n), brightness(255), pin(p) {
	type = LED;
	pinMode(pin, OUTPUT);
}

void Led::turnOn(int brightnessValue) {
	// If brightnessValue is not provided, use the default brightness or the set brightness
	if (brightnessValue == -1) {
		if (brightness == 255) {
			digitalWrite(pin, HIGH);    
		} else {
			analogWrite(pin, brightness);
		}
		} else {
			if (brightnessValue == 255) {
				digitalWrite(pin, HIGH);
		}else{
			analogWrite(pin, brightnessValue);
		}
		brightness = brightnessValue;
	}
}

void Led::turnOff() const {
	analogWrite(pin, 0);  
 	digitalWrite(pin, LOW); 
}

void Led::setLedBrightness(int brightnessValue) {
  brightness = brightnessValue;
}

int Led::getLedBrightness() const {
	return brightness;
}

