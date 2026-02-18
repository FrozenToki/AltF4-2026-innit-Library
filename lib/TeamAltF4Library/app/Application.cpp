#include "Application.h"

Application::Application() : sensorManager(this), sensorList(this), 
	outputManager(this), outputList(this), errorMessages(this), drivingControl(this),
	rotationControl(this), serialComm(this), geometrie(this), loops(this), modi(this), irSensorReader(this) {} 

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

Geometrie& Application::getGeometrie() {
	return geometrie;
	
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