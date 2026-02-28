#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"

class EZ : public SensorBase {
	private: 

	public:
		EZ(int p, String n);
		void update() override;
		float rawData() override;
		
};