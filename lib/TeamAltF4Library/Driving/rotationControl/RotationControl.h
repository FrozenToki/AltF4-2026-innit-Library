#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/Bno055/Bno055.h"
#include <PID_v1.h>
#include "PDController.h"


class Application; 


class RotationControl {
	public: 
		float getRotation(double s = 0);
		double angleError(double setpoint, double input);
		RotationControl(Application* a);

	private:
		double setpoint, input, output;
		Application* app;
		Bno055* bno; 

		PDController* pd;

		PID* pid;

		double kP = 1.5;
		double kI = 0.0;
		double kD = 5.0;
	};

