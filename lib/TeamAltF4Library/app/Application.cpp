#include "Application.h"

Application::Application() : sensorManager(this), sensorList(this), 
	outputManager(this), outputList(this), errorMessages(this), drivingControl(this),
	rotationControl(this), serialComm(this), geometry(this), loops(this), modi(this), 
	irSensorReader(this), states(this), menuManager(this), gameMode(this) {} 

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

RotationControl& Application::getRotationControl() {
	return rotationControl;
}

SerialComm& Application::getSerialComm() {
	return serialComm;
}

Geometry& Application::getGeometry() {
	return geometry;
	
}

Loops& Application::getLoops() {
	return loops;
}

Modi& Application::getModi() {
	return modi;
}

IrSensorReader& Application::getIrSensorReader() {
	return irSensorReader;
}

States& Application::getStates() {
	return states;
}

MenuManager& Application::getMenuManager() {
	return menuManager;
}

GameMode& Application::getGameMode() {
	return gameMode;
}

void Application::softwareReset() {
  SRC_GPR5 = 0x0BAD00F1;
	SCB_AIRCR = 0x05FA0004;
	while (1);
}
