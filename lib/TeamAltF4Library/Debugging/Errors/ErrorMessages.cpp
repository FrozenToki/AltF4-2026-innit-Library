#include "ErrorMessages.h"
#include "app/Application.h"

ErrorMessages::ErrorMessages(Application* a) : app(a) {}

void ErrorMessages::newError(String e, String file) {
	String error = "[" + file + "]" + e;
	addNewErrorToList(error);
}

void ErrorMessages::addNewErrorToList(String e) { 
	for (int i = (Config::MAX_ERROR_MESSAGES -1); i > 0; i--) {
		errorMessages[i] = errorMessages[i-1];
	}
	errorMessages[0] = e;
}

String ErrorMessages::getError(int index) {
	return errorMessages[index];
}

