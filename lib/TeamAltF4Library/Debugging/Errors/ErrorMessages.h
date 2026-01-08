#pragma once
#include <Arduino.h>
#include "Config/Config.h"

// forward declaration
class Application; 

class ErrorMessages {
private:
	Application* app;

	String errorMessages[Config::MAX_ERROR_MESSAGES];
public:
	ErrorMessages(Application* a);

	void newError(String e, String file);
	void addNewErrorToList(String e);

	String getError(int index);
};
