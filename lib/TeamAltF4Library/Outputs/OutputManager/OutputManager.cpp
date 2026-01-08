#include "OutputManger.h"
#include "app/Application.h"

OutputManager::OutputManager(Application* a) : app(a) {}

void OutputManager::createLed(int p, String n) {
	Led* l = new Led(p, n); 
	app->getOutputList().addOutput(l);
}

Led* OutputManager::getLedByName(String n) {
	OutputBase* output = app->getOutputList().getOutputByName(n);
	String outputType;
	outputType = output->getType();
	//if(sensor_type != SensorBase::BUTTON){
	//	__throw_invalid_argument( "Sensor is not a button, dude!" );
	//}
	return static_cast<Led*>(output);
}

void OutputManager::createMotor(int pInA, int pInB, int pPwm, String n) {
	Motor* l = new Motor(pInA, pInB, pPwm, n);
	app->getOutputList().addOutput(l);
}

Motor* OutputManager::getMotorByName(String n) {
	OutputBase* output = app->getOutputList().getOutputByName(n);
	return static_cast<Motor*>(output);
}