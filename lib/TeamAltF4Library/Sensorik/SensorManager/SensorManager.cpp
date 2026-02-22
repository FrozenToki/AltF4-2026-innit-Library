#include "SensorManager.h"
#include "app/Application.h"

SensorManager::SensorManager(Application* a) : app(a) {
	this->createBno055(19, Config::GYRO_NAME);
	
	this->createSr04(5,4,Config::RIGHT_DIST_NAME);
	this->createSr04(29, 28, Config::LEFT_DIST_NAME);
	this->createSr04(27, 26, Config::BACK_DIST_NAME);

	this->createIrSensor(2, Config::IR_SENS_LEFT_NAME, 0.0f);
	this->createIrSensor(3, Config::IR_SENS_RIGHT_NAME, 0.0f);
}


void SensorManager::createButton(int p, String n) {
	Button* btn = new Button(p, n);
	app->getSensorList().addSensor(btn);
}

Button* SensorManager::getButtonByName(String n) {
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	String sensorType;
	sensorType = sensor->getType();
	//if(sensor_type != SensorBase::BUTTON){
	//	__throw_invalid_argument( "Sensor is not a button, dude!" );
	//}
	return static_cast<Button*>(sensor);
}

void SensorManager::createBno055(int p, String n) {
	Bno055* bno = new Bno055(p, n);
	app->getSensorList().addSensor(bno);
}

Bno055* SensorManager::getBno055ByName(String n) {
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	String sensorType;
	sensorType = sensor->getType();
	return static_cast<Bno055*>(sensor);
}

void SensorManager::createSr04(int trig, int echo, String n)	{
	Sr04* sr04 = new Sr04(trig, echo, n);
	app->getSensorList().addSensor(sr04);
}

Sr04 *SensorManager::getSr04ByName(String n)
{
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	return static_cast<Sr04*>(sensor);
}
