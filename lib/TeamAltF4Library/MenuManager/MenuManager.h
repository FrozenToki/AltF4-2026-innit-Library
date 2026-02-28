#pragma once
#include <Arduino.h>
#include "Config/Config.h"
#include "Sensorik/SensorBase/ButtonCross/ButtonCross.h"
#include "Outputs/OutputBase/Ssd1306/Ssd1306.h"
#include "Sensorik/SensorBase/Button/Button.h"

class Application;

class MenuManager {
private: 
	Application* app;
	
	ButtonCross* buttonCross;

	Ssd1306* display;

	Button* greenButton;

	std::vector<void(*)()> modes;
	std::vector<String> modeNames;

	int lastMode = 0;
	int mode = 0;

	int inMode = false;
public: 
	MenuManager(Application* a);
	void addMenuItem(String n, void (*mode)());
	void loop();
};