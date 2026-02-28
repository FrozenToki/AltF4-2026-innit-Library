#include "States.h"
#include "app/Application.h"

States::States(Application *a) : app(a) {

	EEPROM.get(0, ballInHolderThreshould);
	irRing = app->getSensorManager().getIrRingByName(Config::IR_RING_NAME);
	bno055 = app->getSensorManager().getBno055ByName(Config::GYRO_NAME);
	irFR = app->getSensorManager().getIrSensorByName(Config::IR_SENS_RIGHT_NAME);
	irFL = app->getSensorManager().getIrSensorByName(Config::IR_SENS_LEFT_NAME);
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
