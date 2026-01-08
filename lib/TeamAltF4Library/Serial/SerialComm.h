#pragma once
#include <Arduino.h>
#include <Global.h>
#include <vector>
#include "Sensorik/SensorBase/SensorBase.h"  // wichtig: damit die Typen bekannt sind


class SerialComm {
private:

    char sendBuffer[512];    
    String sendString;  

    unsigned int maxSensorValues = 10;
    unsigned int maxOtherValues = 10;
    

    std::vector<String*> otherStuff;
    std::vector<SensorBase*> sensors;

    std::vector<int*> otherValues;
    std::vector<String> otherValuesNames;

    Stream& serial;

    unsigned long lastSendTimeRepeating = 0;
    unsigned long repeatingSendInterval; 

    unsigned long lastSendTimeOneTime = 0;
    unsigned long oneTimeSendInterval; 

public:
    SerialComm(Stream& ser = Serial, unsigned long RepeatingSendInterval = 100, unsigned long OneTimeSendInterval = 500);

    void addSensor(SensorBase* sensor);
    void addOtherValue(int& refVar, String name);
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