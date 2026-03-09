#include "OutputManger.h"
#include "app/Application.h"


OutputManager::OutputManager(Application* a) : app(a) {
	this->createSsd1306(Config::DISPLAY_NAME);

	this->createMotor(21, 20, 10, Config::MOTOR_VL_NAME);
	this->createMotor(32, 33, 11, Config::MOTOR_BA_NAME);
	this->createMotor(36, 38, 12, Config::MOTOR_VR_NAME);
}

// === LED ===

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

// === MOTOR ===

void OutputManager::createMotor(int pInA, int pInB, int pPwm, String n) {
	Motor* l = new Motor(pInA, pInB, pPwm, n);
	app->getOutputList().addOutput(l);
}

Motor* OutputManager::getMotorByName(String n) {
	OutputBase* output = app->getOutputList().getOutputByName(n);
	return static_cast<Motor*>(output);
}

// === SSD_1306 ===

Ssd1306* OutputManager::getSsd1306ByName(String n) {
	OutputBase* output = app->getOutputList().getOutputByName(n);
	return static_cast<Ssd1306*>(output);
}

void OutputManager::createSsd1306(String n) {
	Ssd1306* l = new Ssd1306(n);
	app->getOutputList().addOutput(l);
}


