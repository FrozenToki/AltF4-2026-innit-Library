#include "RotationControl.h"
#include "app/Application.h"


float RotationControl::
getRotation(double target) {

	float cont = bno->getContinuousAngle();          

	while (target < 0)   target += 360;
  while (target >= 360) target -= 360;

	double targetAdjusted = target + floor(cont / 360.0) * 360.0;


	float error = angleError(targetAdjusted, cont);

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
	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME);
	setpoint = 0;

	
	pd = new PDController(kP, kD);
}


