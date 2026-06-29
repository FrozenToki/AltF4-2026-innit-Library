#pragma once
#include <Arduino.h>
#include "Sensorik/SensorManager/SensorManager.h"
#include "Outputs/OutputManager/OutputManger.h"
#include "Config/Config.h"
#include "loops/loops.h"
#include "GameMode/decisionMaking/Modi/Modi.h"

class Application;

class GameMode {
private:
	float degree = 0;
	float strength = 0;

	ApplicationInnit* app;

	Loops loops;
	
	Modi modi;

	SerialReciever* ring;

	Bno055* bno;

	Button* greenBtn;

	Sr04* distRight;
	Sr04* distLeft;
	Sr04*	distBack;

	Ssd1306* display;

	Motor* motor1;
	Motor* motor2;
	Motor* motor3;

	ButtonCross* buttonCross;

	float lastTime = 0;
public:
	GameMode(ApplicationInnit* a);

	void loop();
};
