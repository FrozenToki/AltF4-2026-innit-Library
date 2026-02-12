#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/Button/Button.h"
#include "Sensorik/SensorList/SensorList.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"


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
};

