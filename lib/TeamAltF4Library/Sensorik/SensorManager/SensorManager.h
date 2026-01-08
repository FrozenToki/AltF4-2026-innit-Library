#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/Button/Button.h"
#include "Sensorik/SensorList/SensorList.h"

// forward declaration
class Application; 

// Used to create all the sensors.
class SensorManager {
private:
	Application* app;

	std::vector<Button> buttonStorage;
	int buttonCount;
public:
	SensorManager(Application* a);

	// Creates an instance of the button class and add's that to the sensorlist.
	void createButton(int p, String n);
	// Searches all sensors for the given name and returns it, 
	// as an instance of the button class.
	Button* getButtonByName(String n);
};

