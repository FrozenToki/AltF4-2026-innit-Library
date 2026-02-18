#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/SensorBase.h"
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <vector>


class Bno055 : public SensorBase {
	private:
		std::vector<float> values; 

		float lastAngle = 0;
		float continuousAngle = 0;


		Adafruit_BNO055 bno;
		float calibratedValue = 0;
		uint8_t system, gyro, accel, mag;
	public:
		Bno055 (int p, String n);
		void update() override;
		float rawData() override;
		void calibrate();

		void getCalibrationStatus(); 
		uint8_t getSystem();
		uint8_t getGyro();
		uint8_t getAccel();
		float getContinuousAngle();
};


