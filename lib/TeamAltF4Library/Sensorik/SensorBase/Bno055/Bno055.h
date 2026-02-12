#pragma once
#include "Arduino.h"
#include "Sensorik/SensorBase/SensorBase.h"
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


class Bno055 : public SensorBase {
	private:
		Adafruit_BNO055 bno;
	public:
		Bno055 (int p, String n);
		void update() override;
		float rawData() override;



};
