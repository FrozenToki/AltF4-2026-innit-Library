#pragma once
#include <Arduino.h>
#include "Config/Config.h"
#include "Sensorik/SensorBase/SR04/Sr04.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"

class Application;

class Modi {
public:
	Modi(Application* a);
  void lagOfProgressLeft();
	void mode(float d, float s, float ir);
	void lagOfProgressRight();
 
	void kickOff();

	void setKickOffMode();

	void ballHolder();

	void offWall();

	String getLastMode();
private:
  Application* app;
	float angle = 0;
	float speed = 0;
	float degree = 0;

	bool test = true;
  
	float direction = 0;
	
  Sr04* distRight;
  Sr04* distLeft;
  Sr04*	distBack;

	Bno055* bno;

	String lastModi = "";
};