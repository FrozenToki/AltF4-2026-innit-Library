#include "SensorManager.h"
#include "app/Application.h"

SensorManager::SensorManager(Application* a) : app(a) {}

std::vector<Button> buttonStorage[10];
int buttonCount = 0;


void SensorManager::createButton(int p, String n) {
	Button* btn = &buttonStorage[buttonCount++];
	*btn = Button(p, n);
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