#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/Bno055/Bno055.h"
#include <PID_v1.h>

class Application; 


class RotationControl {
	public: 
		float getRotation(double s = 0);
		float normalizeAngle(float angle);
		RotationControl(Application* a);

	private:
		double setpoint, input, output;
		Application* app;
		Bno055* bno; 

		PID* pid;

		double kP = 2.0;
		double kI = 0.0;
		double kD = 0.0;
	};