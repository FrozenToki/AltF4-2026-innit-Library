#include "RotationControl.h"
#include "app/Application.h"


float RotationControl::getRotation(double target) {

    float cont = bno->getContinuousAngle();          

		int periodes = cont / 360.0f;

		target = target + (360.0f * periodes);

    float error = angleError(target, cont);

    float out = pd->update(error, cont);             

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
	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME);
	setpoint = 0;
	pid->SetMode(AUTOMATIC);
	pid->SetOutputLimits(-255, 255);
	pid->SetSampleTime(10);
	
	pd = new PDController(kP, kD);
}


