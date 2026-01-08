#include "Motor.h"

Motor::Motor(int inA, int inB, int pwm, String n) : OutputBase(n), pinInA(inA), pinInB(inB), pinPwm(pwm) {
    type = MOTOR;

    pinMode(pinInA, OUTPUT);
    pinMode(pinInB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
}

void Motor::turnOn(int speed, int direction) {
    if (direction == Config::FORWARDS) {
        digitalWrite(pinInA, HIGH);
        digitalWrite(pinInB, LOW);
    } 
    else if (direction == Config::BACKWARDS) {
        digitalWrite(pinInA, LOW);
        digitalWrite(pinInB, HIGH);
    }
    int calculatedSpeed = 256 * (speed / 100.0);  
    analogWrite(pinPwm, calculatedSpeed);
} 

void Motor::turnOff() {
    digitalWrite(pinInA, LOW);
    digitalWrite(pinInB, LOW);
    analogWrite(pinPwm, 0);
}

