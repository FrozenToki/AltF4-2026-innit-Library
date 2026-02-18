#include "RotationControl.h"
#include "app/Application.h"


float RotationControl::getRotation(double target) {

    float current = bno->getContinuousAngle();


    float error = angleError(target, current);


    float out = pd->update(error, current);


    if (out > 255) out = 255;
    if (out < -255) out = -255;


    return out / 255.0f;
}



double RotationControl::angleError(double s, double i) {
	double error = s - i;

	if (error > 180)  error -= 360;
	if (error < -180) error += 360;

	return error;
}


RotationControl::RotationControl(Application *a) : app(a) {
	pid = new PID(&input, &output, &setpoint, kP,kI, kD, DIRECT);
	bno = app->getSensorManager().getBno055ByName("GyroSensor1");
	setpoint = 0;
	pid->SetMode(AUTOMATIC);
	pid->SetOutputLimits(-255, 255);
	pid->SetSampleTime(10);
	
	pd = new PDController(kP, kD);
}


