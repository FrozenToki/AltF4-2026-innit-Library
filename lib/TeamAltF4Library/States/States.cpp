#include "States.h"
#include "app/Application.h"

States::States(Application *a) : app(a) {

	EEPROM.get(0, ballInHolderThreshould);
	irRing = app->getSensorManager().getIrRingByName(Config::IR_RING_NAME);
	bno055 = app->getSensorManager().getBno055ByName(Config::GYRO_NAME);
	irFR = app->getSensorManager().getIrSensorByName(Config::IR_SENS_RIGHT_NAME);
	irFL = app->getSensorManager().getIrSensorByName(Config::IR_SENS_LEFT_NAME);

	movingAverage = new MovingAverage(3);
	
	vl = new MovingAverage(3);
	v = new MovingAverage(3);
	vr = new MovingAverage(3);

	ezVL = app->getSensorManager().getEZByName(Config::EZ_VL_NAME);
	ezV = app->getSensorManager().getEZByName(Config::EZ_V_NAME);
	ezVR = app->getSensorManager().getEZByName(Config::EZ_VR_NAME);

	distRight = app->getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);
	distBack = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);
	distLeft = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
}

int States::ballState() {
	float ballAngle = irRing->getAngle();
	ballAngle = app->getGeometry().normalizeAngle(ballAngle);
	float robotAngle = bno055->rawData();
	robotAngle = app->getGeometry().normalizeAngle(robotAngle);
	float realAngle = ballAngle + robotAngle;

	float v1 = irFL->getCalculatedValue();
	float v2 = irFR->getCalculatedValue();

	float ir = (v1 + v2) / 2;

	if (realAngle >= -180 && realAngle <= -70) {
		return Config::BALL_BACK_LEFT;
	}
	else if (realAngle <= 180 && realAngle >= 70) {
		return Config::BALL_BACK_RIGHT;
	}
	else if (ir >= ballInHolderThreshould){
		return Config::BALL_HELD;
	}
	else if (realAngle >= -90 && realAngle <= -25) {
		return Config::BALL_FRONT_LEFT;
	}
	else if (realAngle <= 90 && realAngle >= 25) {
		return Config::BALL_FRONT_RIGHT;
	}
	else {
		return Config::BALL_UPFRONT;
	}
}

int States::getBallInHolderThreshould() {
	return ballInHolderThreshould;
}

void States::setBallInHolderThreshould(int i) {
	ballInHolderThreshould = i;
	EEPROM.put(0, ballInHolderThreshould);
}

int States::robotState() {
	vl->newValue(ezVL->rawData());
	v->newValue(ezV->rawData());
	vr->newValue(ezVR->rawData());

	float i = 0;
	i +=  vr->getAverage();
	i +=  vl->getAverage();
	i +=  v->getAverage();
	i = i / 3;

	movingAverage->newValue(i);

	bool front = false;
	bool back = false;
	bool left = false;
	bool right = false;

	int valid = 0;

	if (movingAverage->getAverage() <= 40) {
		front = true;
		valid += 1;
	}
	
	if (distLeft->rawData() <= 25) {
		left = true;
		valid += 1;
	}

	if (distBack->rawData() <= 25) {
		back = true;
		valid += 1;
	}

	if (distRight->rawData() <= 25) {
		right = true;
		valid += 1;
	}

	
	//bool frontDirection;
	if (app->getGeometry().normalizeAngle(bno055->rawData()) <= -25 || 
	app->getGeometry().normalizeAngle(bno055->rawData()) >= 25) {
		valid = 5;
	}
	


	if (valid > 2) {
		return lastRobotState;
	}
	else if (front && right) {
		lastRobotState = Config::ROBOT_FRONT_RIGHT;
		return lastRobotState;
	}
	else if (front && left) {
		lastRobotState = Config::ROBOT_FRONT_LEFT;
		return lastRobotState;
	}
	else if (front) {
		lastRobotState = Config::ROBOT_FRONT;
		return lastRobotState;
	}
	else if (back && left) {
		lastRobotState = Config::ROBOT_BACK_LEFT;
		return lastRobotState;
	}
	else if (left) {
		lastRobotState = Config::ROBOT_LEFT;
		return lastRobotState;
	}
	else if (back && right) {
		lastRobotState = Config::ROBOT_BACK_RIGHT;
		return lastRobotState;
	}
	else if (right) {
		lastRobotState = Config::ROBOT_RIGHT;
		return lastRobotState;
	}
	else if (back ) {
		lastRobotState = Config::ROBOT_BACK;
		return lastRobotState;
	}
	lastRobotState = 0;
	return 0;
}
