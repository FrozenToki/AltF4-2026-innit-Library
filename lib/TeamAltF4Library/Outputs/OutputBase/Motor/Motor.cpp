#include "Motor.h"

Motor::Motor(int inA, int inB, int pwm, int amp, String n, bool turnDirection) : OutputBase(n), pinInA(inA), pinInB(inB), pinPwm(pwm), pinAmp(amp), turnD(turnDirection) {
    type = MOTOR;

    pinMode(pinInA, OUTPUT);
    pinMode(pinInB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
		pinMode(pinAmp, INPUT);
}

void Motor::turnOn(float speed) {
    int direction;

    if(speed < 0) {
        direction = Config::BACKWARDS;
        speed = speed * -1;
    }
    else {
        direction = Config::FORWARDS;
    }
    
    if (direction == Config::FORWARDS) {
			if (turnD) {
				digitalWrite(pinInB, HIGH);
        digitalWrite(pinInA, LOW);
			}
			else {
				digitalWrite(pinInB, LOW);
        digitalWrite(pinInA, HIGH);
			}
        
    } 
    else if (direction == Config::BACKWARDS) {
			if (turnD) {
				digitalWrite(pinInB, LOW);
        digitalWrite(pinInA, HIGH);
			}
			else {
				digitalWrite(pinInB, HIGH);
        digitalWrite(pinInA, LOW);
			}
        
    }
    int calculatedSpeed = (int)(speed * 255.0f + 0.5f);
    analogWrite(pinPwm, calculatedSpeed);
} 

void Motor::turnOff() {
    digitalWrite(pinInA, LOW);
    digitalWrite(pinInB, LOW);
    analogWrite(pinPwm, 0);
}

void Motor::updateAmperUsage()  {
	int raw = analogRead(pinAmp);

  float voltage = raw * 3.3 / 1023.0;
  float current = voltage / 0.14;

	amperUsage = current;
}

float Motor::getAmperUsage() {
	return amperUsage;
}
