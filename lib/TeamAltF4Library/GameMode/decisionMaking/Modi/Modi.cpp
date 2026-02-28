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
	
}

void Modi::kickOff() {
	lastModi = "kO";
  angle = degree;
	
	speed = Config::HIGH_SPEED;
}

void Modi::setKickOffMode() {
	lastModi = "kO";
}

unsigned long lastTime = 0;

void Modi::ballHolder() {
	lastModi = "bH";
	if (millis() - lastTime > 200){
		speed = Config::HIGH_SPEED;
	}
	else {
		speed = Config::MIDDLE_SPEED;
	}
	
	if (distRight->rawData() > distLeft->rawData()) {
		if (distRight->rawData() <= 40) {
			angle =  30;

		}
		else if (distLeft->rawData() <= 40) {
		angle =  30;

		}
		else {
			angle = degree;
		}

	}
	else {
		if (distRight->rawData() <= 40) {
			angle =  30;
		}
		else if (distLeft->rawData() <= 40) {
		angle =  30;
		}
		else {
			angle = degree;
		}
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
	test = false;
}

String Modi::getLastMode() {
	return lastModi;
}

void Modi::mode(float d, float s, float ir) {
	degree = d;
	test = true;
	direction = 0;
	if (app->getStates().ballState() == Config::BALL_HELD) {
		ballHolder();
	}
	else if (app->getStates().ballState() == Config::BALL_FRONT_RIGHT && distRight->rawData() <= 15.0f) {
		offWall();
	}
	else if (app->getStates().ballState() == Config::BALL_FRONT_LEFT && distLeft->rawData() <= 15.0f) {
		offWall();
	}
  else if (app->getStates().ballState() == Config::BALL_BACK_LEFT) {
		lagOfProgressLeft();
	}
	else if (app->getStates().ballState() == Config::BALL_BACK_RIGHT) {
		lagOfProgressRight();
	}
	else if (lastModi == "oW") {
		digitalWrite(LED_BUILTIN, HIGH);
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
	if (test == true) {
		digitalWrite(LED_BUILTIN, LOW);
		if (angle <= 180 && angle >= 0)
		{
			if (distRight->rawData() <= 14)
			{
				speed = 0.4;
				if (angle <= 90)
				{
					angle = 0;
				}
				else {
					
					angle = -90;
				}
				angle += direction;
			}
		}
		else if (angle <= 0 && angle >= -180)
		{
			if (distLeft->rawData() <= 14)
			{
				speed = 0.4;
				if (angle >= -90)
				{
					angle = 0;
				}
				else {
					angle = 90;
				}
				angle += direction;
			}
		}
		else if (angle <= -90 || angle >= 90)
		{
			
			if (distBack->rawData() <= 35)
			{
				speed = 0.4;
				if (angle <= -90)
				{
					angle = -90;
				}
				else {
					angle = 90;
				}
				angle += direction;
			}
			else if(distBack->rawData() <= 55 || distBack->rawData() == 1000) {
				speed = 0.6;
			}
		}
	}
	


  
	if (s == 0 ) {
		speed = 0;
	}

	if (!(lastModi == "bH")) {
		lastTime = millis();
	}

	//angle = angle - bno->rawData();
	//angle = app->getGeometry().normalizeAngle(angle);

	app->getDrivingControl().drive(angle, speed, app->getRotationControl().getRotation(direction));
}

