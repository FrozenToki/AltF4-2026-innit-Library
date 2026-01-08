#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h" 
#include "Config/Config.h"

// forward declaration
class SensorBase;
class Application;

// Used to save all sensors and acces them easily.
class SensorList {
private:
	Application* app;
  static SensorBase* sensorList[Config::MAX_SENSORS];
  static int sensorCount;
public:
	SensorList(Application* a);
	static void addSensor(SensorBase* s);
	static SensorBase* getSensorByName(const String& n);
	static SensorBase* get(int index);
	static int getSensorCount();
};