#include "Application.h"

Application::Application() : sensorManager(this), sensorList(this), 
	outputManager(this), outputList(this), errorMessages(this), drivingControl(this),
	serialComm(this), rotationControl(this) {} 

SensorList& Application::getSensorList() {
	return sensorList;
}

SensorManager& Application::getSensorManager() {
	return sensorManager;
}

OutputList& Application::getOutputList() {
	return outputList;
}

OutputManager& Application::getOutputManager() {
	return outputManager;
}

Config& Application::getConfig() {
	return config;
}

ErrorMessages& Application::getErrorMessage() {
	return errorMessages;
}

DrivingControl& Application::getDrivingControl() {
	return drivingControl;
}

SerialComm& Application::getSerialComm() {
	return serialComm;
}

RotationControl& Application::getRotationControl() {
	return rotationControl;
}