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


	


	// === SENSOR NAMES ===
	static constexpr const char* RIGHT_DIST_NAME = "distRight";
	static constexpr const char* LEFT_DIST_NAME = "distLeft";
	static constexpr const char* BACK_DIST_NAME = "distBack";

	static constexpr const char* GYRO_NAME = "GyroSens";

	static constexpr const char* IR_SENS_LEFT_NAME = "irL";
	static constexpr const char* IR_SENS_RIGHT_NAME = "irR";

	static constexpr const char* IR_RING_NAME = "IrRing";

	static constexpr const char* BUTTON_CROSS_NAME = "ButtonCross";

	static constexpr const char* GREEN_BUTTON_NAME = "GreenButton";

	static constexpr const char* EZ_VL_NAME = "ezVL";
	static constexpr const char* EZ_V_NAME = "ezV";
	static constexpr const char* EZ_VR_NAME = "ezVR";

	// === OUTPUT NAMES ===

	static constexpr const char* DISPLAY_NAME = "Display";

	static constexpr const char* MOTOR_VL_NAME = "MotorVl";
	static constexpr const char* MOTOR_BA_NAME = "MotorBa";
	static constexpr const char* MOTOR_VR_NAME = "MotorVr";

	// === STATES ===
	static constexpr int BALL_BACK_LEFT = 1;
	static constexpr int BALL_BACK_RIGHT = 2;
	static constexpr int BALL_UPFRONT = 3;
	static constexpr int BALL_HELD = 0;
	static constexpr int BALL_FRONT_LEFT = 4;
	static constexpr int BALL_FRONT_RIGHT = 5;

	static constexpr int ROBOT_FRONT = 1;
	static constexpr int ROBOT_FRONT_RIGHT = 2;
	static constexpr int ROBOT_FRONT_LEFT = 3;
	static constexpr int ROBOT_RIGHT = 4;
	static constexpr int ROBOT_BACK_RIGHT = 5;
	static constexpr int ROBOT_LEFT = 6;
	static constexpr int ROBOT_BACK_LEFT = 7;
	static constexpr int ROBOT_BACK = 8;
	static constexpr int ROBOT_INVALID = 9;

};
