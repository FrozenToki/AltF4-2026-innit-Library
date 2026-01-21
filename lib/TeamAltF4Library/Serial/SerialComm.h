#pragma once
#include <Arduino.h>
#include <vector>
#include "Sensorik/SensorBase/SensorBase.h"  

// forward declaration
class Application; 

class SerialComm {
private:
	Application* app;

	char sendBuffer[512];    
	String sendString;  																							

	unsigned int maxSensorValues = 10;
	unsigned int maxOtherValues = 11;
	

	std::vector<String*> otherStuff;
	std::vector<SensorBase*> sensors;

	std::vector<float*> otherValues;
	std::vector<String> otherValuesNames;

	Stream& serial;

	unsigned long lastSendTimeRepeating = 0;
	unsigned long repeatingSendInterval; 

	unsigned long lastSendTimeOneTime = 0;
	unsigned long oneTimeSendInterval; 

public:
    SerialComm(Application* a, Stream& ser = Serial, unsigned long RepeatingSendInterval = 100, unsigned long OneTimeSendInterval = 500);

    void addSensor(SensorBase* sensor);
    void addOtherValue(float& refVar, String name);
    void addOtherStuff(String& refStr);

    void sendRepeatingData(); // aufrufen in loop()
    void sendOneTimeData(); // einmalig aufrufen in setup()
    
    void sendSensorValues();
    void sendOtherValues();
    void sendOtherStuff();

    void sendSensorNames();
    void sendOtherValuesNames();
    void sendSensorPins();

    void sendValueAsChar(String text, char* charrr,size_t bufferSize,bool newLine = true);
};