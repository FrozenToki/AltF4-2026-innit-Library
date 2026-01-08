#pragma once
#include "Arduino.h"
#include "Outputs/OutputBase/Led/Led.h"
#include "Outputs/OutputBase/Motor/Motor.h"
#include "Outputs/OutputList/OutputList.h"



// forward declaration
class Application;

// Used to create all the outputs.
class OutputManager {
private:
	Application* app;
public:
	OutputManager(Application* a);

	// Creates an instance of the led class and add's that to the outputlist.
	void createLed(int p, String n);
	// Searches all sensors for the given name and returns it, 
	// as an instance of the led class. 
	Led* getLedByName(String n);

	void createMotor(int pInA, int pInB, int pPwm, String n); 
	Motor* getMotorByName(String n);
};
