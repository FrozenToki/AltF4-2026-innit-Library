#include "IrRing.h"

IrRing::IrRing(String n) : SensorBase(0, n) {
	Serial3.begin(115200);
}
// https://forum.arduino.cc/t/serial-input-basics-updated/382007/3



//============

void IrRing::update() {
	this->recvWithStartEndMarkers();
	if (newData == true) {
		strcpy(tempChars, receivedChars);
			// this temporary copy is necessary to protect the original data
			//   because strtok() used in parseData() replaces the commas with \0
		this->parseData();
		//showParsedData();
		newData = false;
	}
}

//============
void IrRing::recvWithStartEndMarkers() {
	static bool recvInProgress = false;
	static byte ndx = 0;
	char rc;

	while (Serial3.available() > 0) {
		rc = Serial3.read();

		// IMMER neu starten bei <
		if (rc == '<') {
			recvInProgress = true;
			ndx = 0;
			continue;
		}

		if (recvInProgress) {
			if (rc == '>') {
				receivedChars[ndx] = '\0';
				recvInProgress = false;
				newData = true;
			}
			else {
				if (ndx < numChars - 1) {
					receivedChars[ndx++] = rc;
				}
				else {
					// Overflow → reset
					recvInProgress = false;
					ndx = 0;
				}
			}
		}
	}
}


//============

void IrRing::parseData() {      // split the data into its parts

    //Serial.print("RAW: ");
    //Serial.println(tempChars);

    if (sscanf(tempChars, "%f,%f", &angleFromRing, &strengthFromRing) == 2) {
        // ok
    } else {
        //Serial.println("Parse failed");
    }
}


//============

void IrRing::showParsedData() {
	Serial.print("angle ");
	Serial.println(angleFromRing);
	Serial.print("strength ");
	Serial.println(strengthFromRing);
}

float IrRing::rawData() {
	return 0.0f;
}

float IrRing::getAngle() {
	return angleFromRing;
}

float IrRing::getStrength() {
	return strengthFromRing;
}
