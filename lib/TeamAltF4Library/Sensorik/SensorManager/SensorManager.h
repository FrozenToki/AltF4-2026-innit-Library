#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/Button/Button.h"
#include "Sensorik/SensorList/SensorList.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"
#include "Sensorik/SensorBase/SR04/Sr04.h"
#include "Sensorik/SensorBase/IrSensors/IrSensors.h"
#include "Sensorik/SensorBase/IrRing/IrRing.h"
#include "Sensorik/SensorBase/ButtonCross/ButtonCross.h"
#include "Sensorik/SensorBase/EZ/EZ.h"

// forward declaration
class Application; 

// Used to create all the sensors.
class SensorManager {
private:
	Application* app;

public:
	SensorManager(Application* a);

	// Creates an instance of the button class and add's that to the sensorlist.
	void createButton(int p, String n);
	// Searches all sensors for the given name and returns it, 
	// as an instance of the button class.
	Button* getButtonByName(String n);

	void createBno055(int p, String n);
	Bno055* getBno055ByName(String n);

	void createSr04(int trig, int echo, String n);
	Sr04* getSr04ByName(String n);

	void createIrSensor(int p, String n, float a);
	IrSensor* getIrSensorByName(String n);

	void createIrRing(String n);
	IrRing* getIrRingByName(String n);

	void createButtonCross(String n, int pin, float v1, float v2, float v3, float v4, float v5);
	ButtonCross* getButtonCrossByName(String n);

	void createEZ(int p, String n);
	EZ* getEZByName(String n);
};

