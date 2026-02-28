#include "SensorManager.h"
#include "app/Application.h"

SensorManager::SensorManager(Application* a) : app(a) {
	this->createBno055(19, Config::GYRO_NAME);
	
	this->createSr04(5,4,Config::RIGHT_DIST_NAME);
	this->createSr04(29, 28, Config::LEFT_DIST_NAME);
	this->createSr04(27, 26, Config::BACK_DIST_NAME);

	this->createIrSensor(2, Config::IR_SENS_LEFT_NAME, 0.0f);
	this->createIrSensor(3, Config::IR_SENS_RIGHT_NAME, 0.0f);

	this->createIrRing(Config::IR_RING_NAME);

	this->createButtonCross(Config::BUTTON_CROSS_NAME, 18, 924, 508, 834, 317, 6898);

	this->createButton(6, Config::GREEN_BUTTON_NAME);
}

// === BUTTON ===
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

// === BNO055 ===
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

// === SR04 ===
void SensorManager::createSr04(int trig, int echo, String n)	{
	Sr04* sr04 = new Sr04(trig, echo, n);
	app->getSensorList().addSensor(sr04);
}

Sr04 *SensorManager::getSr04ByName(String n)
{
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	return static_cast<Sr04*>(sensor);
}

// === IR_RING ===

void SensorManager::createIrRing(String n) {
	IrRing* irRing = new IrRing(n);
	app->getSensorList().addSensor(irRing); 
}

IrRing* SensorManager::getIrRingByName(String n) {
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	return static_cast<IrRing*>(sensor);

}

void SensorManager::createButtonCross(String n, int pin, float v1, float v2, float v3, float v4, float v5) {
	ButtonCross* buttonCross = new ButtonCross(n, pin, v1, v2, v3, v4, v5);
	app->getSensorList().addSensor(buttonCross);
}

ButtonCross *SensorManager::getButtonCrossByName(String n) {
	SensorBase* sensor = app->getSensorList().getSensorByName(n);
	return static_cast<ButtonCross*>(sensor);
}
