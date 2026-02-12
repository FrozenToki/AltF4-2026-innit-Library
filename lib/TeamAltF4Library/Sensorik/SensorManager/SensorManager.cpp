#include "SensorManager.h"
#include "app/Application.h"

SensorManager::SensorManager(Application* a) : app(a) {
	this->createBno055(192, "GyroSensor1");
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