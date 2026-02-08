#include <Arduino.h>
#include "app/Application.h"    
#include "Sensorik/SensorBase/SensorBase.h"
#include "Config/Config.h"
#include "Outputs/OutputBase/Motor/Motor.h"
#include<bits/stdc++.h>
//#include <Adafruit_Sensor.h>

//#include <Adafruit_BNO055.h>
//#include <utility/imumaths.h>
//#include <Wire.h>

//Adafruit_BNO055 bno = Adafruit_BNO055(55);

Application app;


float hellig;
String Nachricht = "";

void softwareReset() {
  SRC_GPR5 = 0x0BAD00F1;
	SCB_AIRCR = 0x05FA0004;
	while (1);
}


void startSerialConnection(bool fastBaudRate, bool waitForConnection) {
	if(fastBaudRate) {
		Serial.begin(115200);
	} else {
		Serial.begin(9600);
	}
	if(waitForConnection){
		#if defined(USBCON) || defined(TEENSYDUINO)
		while (!Serial);
		#endif
	}
	delay(200);
}

Motor* motor1;
Motor* motor2;
Motor* motor3;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	//sstartSerialConnection(true,true);

	digitalWrite(LED_BUILTIN, LOW);

	pinMode(9, INPUT);
	

	//bno.begin();
	//bno.setExtCrystalUse(true);

	

	app.getOutputManager().createMotor(21, 20, 10, "frontLeft");
	app.getOutputManager().createMotor(32, 33, 11, "back");
	app.getOutputManager().createMotor(36, 38, 12, "frontRight");
	
	
	motor1 = app.getOutputManager().getMotorByName("frontLeft");
	motor2 = app.getOutputManager().getMotorByName("back");
	motor3 = app.getOutputManager().getMotorByName("frontRight");
	app.getDrivingControl().addMotor(1, motor1);
	app.getDrivingControl().addMotor(2, motor2);
	app.getDrivingControl().addMotor(3, motor3);
	
	
	Serial3.begin(115200);

	pinMode(9, INPUT_PULLDOWN);
}

float degree = 0;

float i = 0;
void loop() {	
	if (Serial3.available())  {
		//Serial.println(Serial3.readStringUntil('\n'));
		String input = Serial3.readStringUntil('\n');
		degree = input.toFloat();
	}
	if(digitalRead(9)== HIGH) {
		app.getDrivingControl().drive(degree, 1, 0);
	} 
	else {
		motor1->turnOff();
		motor2->turnOff();
		motor3->turnOff();
	}

	//sensors_event_t event; 
	//bno.getEvent(&event);

	//Serial.println(event.orientation.x);
	//delay(100);
}

