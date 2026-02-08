#include "Motor.h"

Motor::Motor(int inA, int inB, int pwm, String n) : OutputBase(n), pinInA(inA), pinInB(inB), pinPwm(pwm) {
    type = MOTOR;

    pinMode(pinInA, OUTPUT);
    pinMode(pinInB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
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
        digitalWrite(pinInB, HIGH);
        digitalWrite(pinInA, LOW);
    } 
    else if (direction == Config::BACKWARDS) {
        digitalWrite(pinInB, LOW);
        digitalWrite(pinInA, HIGH);
    }
    int calculatedSpeed = (int)(speed * 255.0f + 0.5f);
    analogWrite(pinPwm, calculatedSpeed);
} 

void Motor::turnOff() {
    digitalWrite(pinInA, LOW);
    digitalWrite(pinInB, LOW);
    analogWrite(pinPwm, 0);
}

