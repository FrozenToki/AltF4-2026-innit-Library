#pragma once 
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"

const byte numChars = 32;

class IrRing : public SensorBase {
private:
	
	char receivedChars[numChars];
	char tempChars[numChars];        // temporary array for use when parsing

			// variables to hold the parsed data
	
	float strengthFromRing = 0.0;
	float angleFromRing = 0.0;

	boolean newData = false;

public:
	IrRing(String n);
	void update() override;
	void recvWithStartEndMarkers();
	void parseData();
	void showParsedData();

	float rawData() override;

	float getAngle();
	float getStrength();
};