#include "Modi.h"
#include "app/Application.h"



Modi::Modi(Application* a) : app(a) {
  distRight = app->getSensorManager().getSr04ByName("distRight");
	distLeft = app->getSensorManager().getSr04ByName("distLeft");
	distBack = app->getSensorManager().getSr04ByName("distBack");
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

void Modi::ballHolder() {
	lastModi = "bH";
	speed = Config::MIDDLE_SPEED;
	if (distRight->rawData() > distLeft->rawData()) {
		if (distRight->rawData() <= 40) {
			angle = degree - 30;

		}
		else if (distLeft->rawData() <= 40) {
		angle = degree + 30;

		}
		else {
			angle = degree;
		}

	}
	else {
		if (distRight->rawData() <= 40) {
			angle = degree - 30;
		}
		else if (distLeft->rawData() <= 40) {
		angle = degree + 30;
		}
		else {
			angle = degree;
		}
	}


}

void Modi::mode(float d, float s, float ir) {
	degree = d;
	direction = 359;
	if (ir >= 18000) {
		ballHolder();
	}
  if (degree >= -180 && degree <= -70) {
		lagOfProgressLeft();
	}
	else if (degree <= 180 && degree >= 70) {
		lagOfProgressRight();
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
			}
			else if(distBack->rawData() <= 55 || distBack->rawData() == 1000) {
				speed = 0.6;
			}
		}

		if (s == 0 ) {
			speed = 0;
		}

	app->getDrivingControl().drive(angle, speed, app->getRotationControl().getRotation(direction));
}

