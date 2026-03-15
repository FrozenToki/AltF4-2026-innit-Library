#include "Modi.h"
#include "app/Application.h"



Modi::Modi(Application* a) : app(a) {
  distRight = app->getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);
	distLeft = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	distBack = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);

	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME); 

	lastModi = "kO";
}

void Modi::lagOfProgressLeft() {

	lastModi = "lOPL";

	angle = degree - 35;
	speed = Config::HIGH_SPEED;

  if (degree >= -25)
	{
		speed = Config::MIDDLE_SPEED;
		angle = degree;
	}
	else if (degree > -35) {
		angle = degree;
		speed = Config::LOW_SPEED;
	} else if (degree > -70) {
		speed = Config::MIDDLE_SPEED;
		angle = degree - 10;
	}
	fixDrivingAngle();
}
void Modi::lagOfProgressRight() {
	lastModi = "lOPR";

	angle = degree + 35;
	speed = Config::HIGH_SPEED;

  if (degree <= 25) {
		speed = Config::MIDDLE_SPEED;
		angle = degree;
	}
	else if (degree < 35) {
		angle = degree;
		speed = Config::LOW_SPEED;
	} else if (degree < 70) {
		speed = Config::MIDDLE_SPEED;
		angle = degree + 10;
	}
	fixDrivingAngle();

}

void Modi::kickOff() {
	lastModi = "kO";
  angle = degree;
	
	speed = Config::HIGH_SPEED;
	fixDrivingAngle();
}

void Modi::setKickOffMode() {
	lastModi = "kO";
}

unsigned long lastTime = 0;
float lastAngle = 0;

void Modi::ballHolder() {
	lastModi = "bH";
	if (millis() - lastTime > 200){
		speed = Config::HIGH_SPEED;
	}
	else {
		speed = Config::MIDDLE_SPEED;
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

	fixDrivingAngle();
}

void Modi::ballHolderFrontLeft() {
	lastModi = "bHFL";
	speed = Config::MIDDLE_SPEED;
	
	if (app->getStates().robotState() == Config::ROBOT_FRONT || 
			app->getStates().robotState() == Config::ROBOT_FRONT_LEFT) {
		angle = 100;
	}
	else {
		angle = 80;
	}

	direction = 10;
	fixDrivingAngle();
	
}

void Modi::ballHolderFrontRight() {
	lastModi = "bHFR";
	speed = Config::MIDDLE_SPEED;
	
	if (app->getStates().robotState() == Config::ROBOT_FRONT || 
			app->getStates().robotState() == Config::ROBOT_FRONT_RIGHT) {
		angle = -100;
	}
	else {
		angle = -80;
	}

	direction = -10;
	fixDrivingAngle();
}

void Modi::ballHolderFront() {
	if (robotAngle < 35 && robotAngle > -35) {
		if (distLeft->rawData() > distRight->rawData()) {
			ballHolderFrontLeft();
		}
		else {
			ballHolderFrontRight();
		}
	}
	else {
		ballHolderFrontLeft();
	}
	
}

void Modi::offWall() {
	lastModi = "oW";
	speed = Config::MIDDLE_SPEED;
	direction = degree + bno->rawData();

	if (direction >= 0) {
		direction -=10;
	}
	else {
		direction +=10;
	}
	float robotAngle = app->getGeometry().normalizeAngle(bno->rawData());
	angle = -robotAngle;
}

void Modi::turnToBall() {
	lastModi = "tB";
	
	if (degree < 15 && degree > -15) {
		speed = Config::MIDDLE_SPEED;
	}
	else {
		speed = -Config::LOW_SPEED;

	}
	
	direction = degree + bno->rawData();

	angle = robotAngle;
}

void Modi::toBallLeft() {
	lastModi = "tBL";
	
	speed = Config::MIDDLE_SPEED;
	
	direction = degree + bno->rawData();

	// Nah an der linken Wand
	if (distLeft->rawData() <= 8)
	{
		angle = 10;
		fixDrivingAngle();
	}
	else if (distLeft->rawData() > 8) {
		angle = -10;
 		fixDrivingAngle();
	}else{
		angle = robotAngle;
	}

}

String Modi::getLastMode() {
	return lastModi;
}

void Modi::fixDrivingAngle(){
	//angle = angle - robotAngle;
}

void Modi::mode(float d, float s) {
	degree = d;
	direction = 0;

	fixDrivingAngl = true;

	speed = Config::MIDDLE_SPEED;
	bool newModi = true;

	
	//robotAngle = bno->rawData();
	//robotAngle = app->getGeometry().normalizeAngle(robotAngle);
	//degree = degree - robotAngle;
	
	
	//// === ROBOTER FRONT LEFT ===
	//if (app->getStates().robotState() == Config::ROBOT_FRONT_LEFT) {
	//	// === BALL HELD ===
	//	if (app->getStates().ballState() == Config::BALL_HELD) {
	//		ballHolderFrontLeft();
	//	}
	//	// === BACK LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	// === BACK RIGHT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	// === FRONT LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_LEFT) {
	//		turnToBall();
	//	}
	//	// === FRONT RIGHT ===
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_RIGHT) {
	//		turnToBall();
	//	}
	//	else {
	//		newModi = false;
	//	}
	//}
	//else if (app->getStates().robotState() == Config::ROBOT_BACK_LEFT) {
	//	angle = 45;
	//}
	//else if (app->getStates().robotState() == Config::ROBOT_BACK_RIGHT) {
	//	angle = -45;
	//}
	
	//else if (app->getStates().robotState() == Config::ROBOT_FRONT_RIGHT) {
	//	angle = -135;
	//}	
	//// === FRONT ===
	//else if (app->getStates().robotState() == Config::ROBOT_FRONT) {
	//	// === FRONT RIGHT ===
	//	if (app->getStates().ballState() == Config::BALL_FRONT_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	// === FRONT LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	// === BACK RIGHT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	// === BACK LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	// === HELD ===
	//	else if (app->getStates().ballState() == Config::BALL_HELD) {
	//		ballHolderFront();
	//	}
	//	else {
	//		newModi = false;
	//	}
		
	//}
	//else if (app->getStates().robotState() == Config::ROBOT_BACK) {
	//	angle = 0;
	//}
	//else if (app->getStates().robotState() == Config::ROBOT_RIGHT) {
	//	angle = -90;
	//}
	//// === LEFT ===
	//else if (app->getStates().robotState() == Config::ROBOT_LEFT) {
	//	// === BALL HELD ===
	//	if (app->getStates().ballState() == Config::BALL_HELD) {
	//		ballHolder();
	//	}
	//	// === BACK LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	// === BACK RIGHT ===
	//	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	// === FRONT LEFT ===
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_LEFT) {
	//		toBallLeft();
	//	}
	//	// === FRONT RIGHT ===
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	else {
	//		newModi = false;
	//	}
	
		
	//}
	//else if (app->getStates().robotState() == 0) {
	//	if (app->getStates().ballState() == Config::BALL_HELD) {
	//		ballHolder();
	//	}
	//	else if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_LEFT) {
	//		lagOfProgressLeft();
	//	}
	//	else if (app->getStates().ballState() == Config::BALL_FRONT_RIGHT) {
	//		lagOfProgressRight();
	//	}
	//	else {
	//		newModi = false;
	//	}

	//}	

	
	if (app->getStates().ballState() == Config::BALL_HELD) {
		ballHolder();
	}
	if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
		lagOfProgressLeft();
	}
	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
		lagOfProgressRight();
	}
	else {
		newModi = false;
	}

	if (app->getStates().robotState() == Config::ROBOT_BACK) {
		if (angle < -90 ) {
			if (distBack->rawData() <  8) {
				angle = -80;
			}
			else {
				angle = -100;
			}
			fixDrivingAngle();
		}
		else if (angle > 90) {
			if (distBack->rawData() <  8) {
				angle = 80;
			}
			else {
				angle = 100;
			}
			fixDrivingAngle();
		}
	}

	if (app->getStates().robotState() == Config::ROBOT_RIGHT) {
		if (angle > 90 ) {
			if (distRight->rawData() <  8) {
				angle = -170;
			}
			else {
				angle = 170;
			}
			fixDrivingAngle();
		}
		else if (angle < -145) {
			
			angle = -135;
			
			fixDrivingAngle();
		}
	}

	if (app->getStates().robotState() == Config::ROBOT_LEFT) {
		if (angle < -90 ) {
			if (distLeft->rawData() <  8) {
				angle = 170;
			}
			else {
				angle = -170;
			}
			fixDrivingAngle();
		}
		else if (angle > 145) {
			
			angle = 135;
			
			fixDrivingAngle();
		}
	}

	//if (app->getStates().robotState() == Config::ROBOT_FRONT_LEFT) {
	//	angle = 135;
	//}
	//else if (app->getStates().robotState() == Config::ROBOT_FRONT_RIGHT) {
	//	angle = -135;
	//}
	//else if ( app->getStates().robotState() == Config::ROBOT_FRONT) {
	//	if (angle > -90 && angle <= 0) {
	//		angle = -95;
	//	}
	//	else if (angle < 90 && angle >= 0) {
	//		angle =  95;
	//	}
	//}




	
		//if (app->getStates().robotState() == Config::ROBOT_BACK_LEFT && distRight->rawData() > 75) {
		//	if (angle < -65) {
		//		angle = angle + 180;
		//	}
		//}
		//else if (app->getStates().robotState() == Config::ROBOT_BACK_RIGHT && distLeft->rawData() > 75) {
		//	if (angle > 65) {
		//		angle = angle - 180;
		//	}
		//}

	//}


	if (newModi == false) {
		if (lastModi == "oW") {
			offWall();
		}
		else if (lastModi == "bH") {
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
		else if (lastModi == "tB") {
			turnToBall();
		}
		else if (lastModi == "bHFL") {
			ballHolderFrontLeft();
		}
		else if (lastModi == "bHFR") {
			ballHolderFrontRight();
		}
		else if (lastModi == "tBL") {
			toBallLeft();
		}
		
	}

	if (s == 0) {
		speed = 0;
	}
	
	lastRobotState = app->getStates().ballState();

	degree = app->getGeometry().normalizeAngle(degree);

	

	while (angle > 180) angle -= 360;
	while (angle < -180) angle += 360;




	//if (!(lastDirection == direction)) {
	//	if (lastDirectionTime - millis() >50) {
	//		if (direction > lastDirection) {
	//			newDirection = lastDirection + 1;
	//		}
	//		else if (direction < lastDirection) {
	//			newDirection = lastDirection + -1;
	//		}
	//	}
	//	else {
	//		newDirection = lastDirection;
	//	}
		
	//}
	//else {
	//	newDirection = direction;
	//}

	//lastDirection = newDirection;




	app->getDrivingControl().drive(angle, speed, app->getRotationControl().getRotation(direction));
}

