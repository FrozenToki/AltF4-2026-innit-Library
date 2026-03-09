#pragma once
#include <Arduino.h>
#include "Config/Config.h"
#include "Sensorik/SensorBase/SR04/Sr04.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"

class Application;

class Modi {
public:
	Modi(Application* a);

	void mode(float d, float s);

	void lagOfProgressLeft();
	void lagOfProgressRight();
 
	void kickOff();

	void setKickOffMode();

	void ballHolder();
	void ballHolderFrontLeft();
	void ballHolderFrontRight();
	void ballHolderFront();

	void offWall();

	void turnToBall();
	
	void toBallLeft();

	String getLastMode();

	void fixDrivingAngle();

private:
  Application* app;
	float angle = 0;
	float speed = 0;
	float degree = 0;

	int lastRobotState = 0;

	bool test = true;
  
	float direction = 0;
	
  Sr04* distRight;
  Sr04* distLeft;
  Sr04*	distBack;

	Bno055* bno;

	String lastModi = "";

	float robotAngle = 0;
};