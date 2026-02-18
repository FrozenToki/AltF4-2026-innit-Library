#include "Button.h"

Button::Button(int p, String n) : SensorBase(p, n) {
	type = BUTTON;
	pinMode(pin, INPUT_PULLDOWN);  
}

void Button::update() {
	value = digitalRead(pin);
}

float Button::rawData() {
	return value;
}

bool Button::isPressed() const {
	return value;
}
