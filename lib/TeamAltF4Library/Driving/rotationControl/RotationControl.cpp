#include "RotationControl.h"
#include "app/Application.h"

float RotationControl::getRotation(double s) {
	float rotation = bno->rawData();
	
	s = this->normalizeAngle(s);
	rotation = this->normalizeAngle(rotation);

	input = rotation;
	setpoint = s;

	pid->Compute();

	float outputValue = output / 255.0f;
	return outputValue; 
}

RotationControl::RotationControl(Application *a) : app(a) {
	pid = new PID(&input, &output, &setpoint, kP,kI, kD, DIRECT);
	bno = app->getSensorManager().getBno055ByName("GyroSensor1");
	setpoint = 0;
	pid->SetMode(AUTOMATIC);
	pid->SetOutputLimits(-255, 255);
}


float RotationControl::normalizeAngle(float angle) {
	while (angle < 0) angle += 360;
	while (angle >= 360) angle -= 360;


	if (angle > 180)
		angle -= 360;

	return angle;
}
