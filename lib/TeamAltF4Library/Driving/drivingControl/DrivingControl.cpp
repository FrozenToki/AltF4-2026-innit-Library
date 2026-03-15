#include "DrivingControl.h"
#include "app/Application.h"

DrivingControl::DrivingControl(Application* a) : app(a) {
	ring = app->getSensorManager().getIrRingByName(Config::IR_RING_NAME);
	distanceThreshold = EEPROM.get(1, distanceThreshold);
}

void DrivingControl::drive(float angle, float motorSpeed, float rotation) {
  
	motorSpeed = motorSpeed * getAmpFactor();
	
	float speedY = cos(angle * (PI / 180.0));
    float speedX = sin(angle * (PI / 180.0));
    speedY = speedY * motorSpeed;
    speedX = speedX * motorSpeed;
    
    
    float angleMotor1 = 60 * (PI / 180.0);
    float angleMotor2 = 180 * (PI / 180.0);
    float angleMotor3 = 300* (PI / 180.0);

    float motor1 = cos(angleMotor1) * speedX + sin(angleMotor1) * speedY + rotation;
    float motor2 = cos(angleMotor2) * speedX + sin(angleMotor2) * speedY + rotation;
    float motor3 = cos(angleMotor3) * speedX + sin(angleMotor3) * speedY + rotation;

		if (motor1 < -1.0f) {
			motor1 = -1.0f;
		}
		else if (motor1 > 1.0f) {
			motor1 = 1.0f;
		}

		if (motor2 < -1.0f) {
			motor2 = -1.0f;
		}
		else if (motor2 > 1.0f) {
			motor2 = 1.0f;
		}

		if (motor3 < -1.0f) {
			motor3 = -1.0f;
		}
		else if (motor3 > 1.0f) {
			motor3 = 1.0f;
		}
    
    frontLeft->turnOn(motor1);
    back->turnOn(motor2);
    frontRight->turnOn(motor3);

}

void DrivingControl::addMotor(int index, Motor* motor) {
    if (index == 1) {
        frontLeft = motor;
    }
    else if (index == 2) {
        back = motor;
    }
    else if (index == 3) {
        frontRight = motor;
    }
}

void DrivingControl::turnOff() {
	frontLeft->turnOff();
	back->turnOff();
	frontRight->turnOff();
}

void DrivingControl::setDistanceThreshold(float dist) {
	distanceThreshold = dist;
	EEPROM.put(1, distanceThreshold);
}

float DrivingControl::getAmpFactor() {
	frontLeft->updateAmperUsage();
	back->updateAmperUsage();
	frontRight->updateAmperUsage();
	

	if (frontRight->getAmperUsage() > 1.1 || back->getAmperUsage() > 1.1 || frontLeft->getAmperUsage() > 1.1) {
		if (ampFactor <= 0) {
			ampFactor = 0;
		}
		else {
			ampFactor -= 0.02;
		}
	}
	//else if ((frontLeft->getAmperUsage() + back->getAmperUsage() + frontRight->getAmperUsage()) > 6) {
	//	if (ampFactor <= 0) {
	//		ampFactor = 0;
	//	}
	//	else {
	//		ampFactor -= 0.02;
	//	}
	//}
	else {
		if (ampFactor >= 1) {
			ampFactor = 1;
		}
		else {
			ampFactor += 0.02;
		}
	}

	//float ringStrenght = ring->getStrength() * 8;
 
	//float distanceRaw = ((1/sqrt(ringStrenght)) * 2000);
	//float distance = (distanceRaw -  65)*2;

	//if (distance > 40) {
	//	digitalWrite(LED_BUILTIN,HIGH);
	//	return 1;
	//}
	//digitalWrite(LED_BUILTIN,LOW);
	return ampFactor;
}
