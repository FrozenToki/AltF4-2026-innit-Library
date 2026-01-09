#include "DrivingControl.h"
#include "app/Application.h"

DrivingControl::DrivingControl(Application* a) : app(a) {}

void DrivingControl::drive(float angle, float motorSpeed, float rotation) {
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