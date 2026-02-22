#pragma once
#include <Arduino.h>

// Used to get variables that will not be change while running the programm.
// 
// Easy acces about app->getConfig().NameOfTheVariable when the variable is used 
// while the programm is running. If the variable is essential for the compiler, 
// it needs to be accesed directly with Config::NameOfTheVariable.  
class Config {
public:
	static constexpr int MAX_SENSORS = 30;
	static constexpr int MAX_OUTPUTS = 30;  
	static constexpr int MAX_ERROR_MESSAGES = 5;    
	static constexpr int FORWARDS = 1;
	static constexpr int BACKWARDS = 0;
  static constexpr float LOW_SPEED = 0.4;
	static constexpr float MIDDLE_SPEED = 0.6;
	static constexpr float HIGH_SPEED = 0.9;

	static constexpr int COUNT_IR_SENSOR = 2;


	static constexpr const char* RIGHT_DIST_NAME = "distRight";
	static constexpr const char* LEFT_DIST_NAME = "distLeft";
	static constexpr const char* BACK_DIST_NAME = "distBack";

	static constexpr const char* GYRO_NAME = "GyroSens";

	static constexpr const char* IR_SENS_LEFT_NAME = "irL";
	static constexpr const char* IR_SENS_RIGHT_NAME = "irR";
};
