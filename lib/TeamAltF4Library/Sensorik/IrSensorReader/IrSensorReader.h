#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/IrSensors/IrSensors.h"
#include "config/Config.h"

// forward declaration
class Application;

class IrSensorReader {
private:
	int lastReadingTime;
	Application* app;
 	IrSensor* irSensList[Config::COUNT_IR_SENSOR];
public:
	IrSensorReader(Application* a);
	void readAll(int ticks, bool time = false, long unsigned int timeInMicSec = 0);
	void setAll();
	void getAllValues(float array[]);
	float frequencyInMilSec(int timeInMicSec, float sensHits);
};