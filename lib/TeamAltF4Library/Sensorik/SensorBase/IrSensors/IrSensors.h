#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"


class IrSensor : public SensorBase {
private:
	float angle;
	float avrgAngle;
	float calculatedValue;

public:
	IrSensor(int p, String n, float a);
	void update() override;
	float rawData() override;
	float getCalculatedValue();
	void setCalculatedValue(float v);
	void resetValue();


	float getAngle();

};  