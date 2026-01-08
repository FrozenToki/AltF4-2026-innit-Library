#pragma once
#include <Arduino.h>
#include "Outputs/OutputBase/Outputs.h"
#include "Config/Config.h"

// forward declaration
class OutputBase;
class Application;

// Used to save all outputs (like motors, displays, leds etc.) and acces them easily.
class OutputList {
private:
	Application* app;
	static OutputBase* outputList[Config::MAX_OUTPUTS];
	static int outputCount;
public:
	OutputList(Application* a);
	static void addOutput(OutputBase* s);
	static OutputBase* getOutputByName(const String& n);
	static OutputBase* get(int index);
	static int getOutputCount();
};