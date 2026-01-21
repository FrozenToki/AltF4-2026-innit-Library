#include "SerialComm.h"
#include "app/Application.h"

SerialComm::SerialComm(Application* a, Stream& ser, unsigned long RepeatingSendInterval, unsigned long OneTimeSendInterval)
    : app(a), serial(ser), repeatingSendInterval(RepeatingSendInterval), oneTimeSendInterval(OneTimeSendInterval) {
    
}




void SerialComm::sendRepeatingData() {
	unsigned long currentMillis = millis();
	if (currentMillis - lastSendTimeRepeating >= repeatingSendInterval) {
		lastSendTimeRepeating = currentMillis;
		sendString = ""; 
		sendSensorValues();
		sendOtherValues();
		sendOtherStuff();
		sendValueAsChar(sendString, sendBuffer, sizeof(sendBuffer));
	}
}

void SerialComm::sendOneTimeData() {
	unsigned long currentMillis = millis();
	if (currentMillis - lastSendTimeOneTime >= oneTimeSendInterval) {
		lastSendTimeOneTime = currentMillis;
		sendString = ""; 
		sendSensorNames();
		sendOtherValuesNames();
		sendSensorPins();
		sendValueAsChar(sendString, sendBuffer, sizeof(sendBuffer));
	}
}

void SerialComm::addSensor(SensorBase* sensor) {
	if (sensors.size() == maxSensorValues) {
		String errorMessage = "more than " + String(maxSensorValues) + " Sensors";
		app->getErrorMessage().newError(errorMessage, "SerialComm.cpp");
	} else {
		sensors.push_back(sensor);
	}
}

void SerialComm::addOtherValue(float& refVar, String name) {
	if (otherValues.size() == maxOtherValues) {
		String errorMessage = "more than " + String(maxOtherValues) + " Other Values";
		app->getErrorMessage().newError(errorMessage, "SerialComm.cpp");
	} else {
		otherValuesNames.push_back(name);
		otherValues.push_back(&refVar);
	}
}

void SerialComm::addOtherStuff(String& refStr){
	otherStuff.push_back(&refStr);  
}

void SerialComm::sendSensorValues() {
	for (unsigned int i = 0; i < maxSensorValues; i++) {
		//sensors[i]->update(); // Werte aktualisieren
		if (i < sensors.size()) {
			sendString += sensors[i]->rawData();  
		} else {
			sendString += "";
		}
		sendString += ",";
		
	}
}

void SerialComm::sendOtherValues() {
	for (size_t i = 0; i < maxOtherValues; i++) {
		if (i < otherValues.size()) {
			sendString += *otherValues[i];  
		} else {
			sendString += "";
		}
		sendString += ",";
	}
}

void SerialComm::sendOtherStuff() {
	for (size_t i = 0; i < otherStuff.size(); i++) {
		sendString += *otherStuff[i];
		if (i < otherStuff.size() - 1) {
			sendString += ","; 
		}
	}
}

void SerialComm::sendSensorNames() {
	for (unsigned int i = 0; i < maxSensorValues; i++) {
		if (i < sensors.size()) {
			sendString += sensors[i]->getName();  
		} else {
			sendString += "";  
		}
		sendString += ",";
		
	}
}

void SerialComm::sendOtherValuesNames() {
	for (unsigned int i = 0; i < 10; i++) { 
		if (i < otherValuesNames.size()) {
			sendString += otherValuesNames[i];  
		} else {
			sendString += "";
		}
		sendString += ",";
	}
}

void SerialComm::sendSensorPins() {
	for (unsigned int i = 0; i < 10; i++) {
		if (i < sensors.size()) {
			sendString += sensors[i]->getPin();  
		} else {
				sendString += ""; 
		}
		sendString += ",";
	}
}

void SerialComm::sendValueAsChar(String text, char* charrr,size_t bufferSize,bool newLine ) {
	snprintf(charrr, bufferSize,"%s", text.c_str());
	if (newLine) {
		Serial.println(charrr);
	} else {
		Serial.print(charrr);
	}
}