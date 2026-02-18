#include "IrSensors.h"

IrSensor::IrSensor(int p, String n, float a) : SensorBase(p, n), angle(a) {
	pinMode(p, INPUT_PULLUP);
}

float IrSensor::getAngle() {
	return angle;
}

void IrSensor::update() {
	if (digitalRead(pin) == LOW) {
		value++;
	}
}

float IrSensor::rawData() {
	return value;
}

void IrSensor::resetValue() {
	value = 0.0f;
}

float IrSensor::getCalculatedValue(){
	return calculatedValue;
}

void IrSensor::setCalculatedValue(float v) {
	calculatedValue = v;
}

