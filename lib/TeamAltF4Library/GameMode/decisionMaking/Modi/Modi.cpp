#include "Modi.h"
#include "app/ApplicationInnit.h"



Modi::Modi(ApplicationInnit* a) : app(a),states(a) {
  distRight = app->getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);
	distLeft = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	distBack = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);

	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME); 

	lastModi = "kO";
}

void Modi::lagOfProgressLeft() {

	lastModi = "lOPL";

	angle = degree - 35;
	speed = InnitConfig::HIGH_SPEED;

  if (degree >= -25)
	{
		speed = InnitConfig::MIDDLE_SPEED;
		angle = degree;
	}
	else if (degree > -35) {
		angle = degree;
		speed = InnitConfig::LOW_SPEED;
	} else if (degree > -70) {
		speed = InnitConfig::MIDDLE_SPEED;
		angle = degree - 10;
	}
	
}
void Modi::lagOfProgressRight() {
	lastModi = "lOPR";

	angle = degree + 35;
	speed = InnitConfig::HIGH_SPEED;

  if (degree <= 18) {
		speed = InnitConfig::MIDDLE_SPEED;
		angle = degree;
	}
	else if (degree < 35) {
		angle = degree + 10;
		speed = InnitConfig::LOW_SPEED;
	} else if (degree < 70) {
		speed = InnitConfig::MIDDLE_SPEED;
		angle = degree + 10;
	}
	

}

void Modi::kickOff() {
	lastModi = "kO";
  angle = degree;
	
	speed = InnitConfig::HIGH_SPEED;
	
}

void Modi::setKickOffMode() {
	lastModi = "kO";
}

unsigned long lastTime = 0;
float lastAngle = 0;

void Modi::ballHolder() {
	lastModi = "bH";
	if (millis() - lastTime > 200){
		speed = InnitConfig::HIGH_SPEED;
	}
	else {
		speed = InnitConfig::MIDDLE_SPEED;
	}
	
	if (distRight->rawData() > distLeft->rawData()) {
		if (distRight->rawData() <= 100) {
			angle =  -30;


		}
		else if (distLeft->rawData() <= 100) {
		angle =  30;


		}
		else {
			angle = degree;
		}

	}
	else {
		if (distRight->rawData() <= 100) {
			angle =  -30;

		}
		else if (distLeft->rawData() <= 100) {
		angle =  30;

		}
		else {
			angle = degree;
			direction = 0;
		}
	}

}


String Modi::getLastMode() {
	return lastModi;
}



void Modi::mode(float d, float s) {

	int ballState = states.ballState();
	int robotState = states.robotState();

	degree = d;
	direction = 0;
	speed = InnitConfig::MIDDLE_SPEED;

	bool newModi = true;

	

	
	if (ballState == Config::BALL_HELD) {
		ballHolder();
	}
	if (ballState == Config::BALL_BACK_LEFT) {
		lagOfProgressLeft();
	}
	else if (ballState == Config::BALL_BACK_RIGHT) {
		lagOfProgressRight();
	}
	else {
		newModi = false;
	}

	if (robotState == Config::ROBOT_BACK) {
		if (angle < -90 ) {
			if (distBack->rawData() <  8) {
				angle = -80;
			}
			else {
				angle = -100;
			}
			
		}
		else if (angle > 90) {
			if (distBack->rawData() <  8) {
				angle = 80;
			}
			else {
				angle = 100;
			}
			
		}
	}

	if (robotState == Config::ROBOT_RIGHT) {
		if (angle > 90 ) {
			if (distRight->rawData() <  8) {
				angle = -170;
			}
			else {
				angle = 170;
			}
			
		}
		else if (angle < -145) {
			
			angle = -135;
			
			
		}
	}

	if (robotState == Config::ROBOT_LEFT) {
		if (angle < -90 ) {
			if (distLeft->rawData() <  8) {
				angle = 170;
			}
			else {
				angle = -170;
			}
			
		}
		else if (angle > 145) {
			angle = 135;
		}
	}


	if (newModi == false) {

		if (lastModi == "bH") {
			ballHolder();
			
		}
		else if (lastModi == "kO") {
			kickOff();
		}
		else if (lastModi == "lOPR") {
			lagOfProgressRight();
		} 
		else if (lastModi == "lOPL") {
			lagOfProgressLeft();
		}
		
	}

	if (s == 0) {
		speed = 0;
	}
	
	lastRobotState = ballState;

	degree = app->getGeometry().normalizeAngle(degree);

	while (angle > 180) angle -= 360;
	while (angle < -180) angle += 360;



	app->getDrivingControl().drive(angle, speed, app->getRotationControl().getRotation(direction));
}

