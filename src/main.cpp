#include <Arduino.h>
#include "app/Application.h"    
#include "Sensorik/SensorBase/SensorBase.h"
#include "Config/Config.h"
#include "Outputs/OutputBase/Motor/Motor.h"



Application app;


float hellig;
String Nachricht = "";

void sensorSends(){
	app.getSerialComm().addSensor(app.getSensorManager().getButtonByName("Btn1"));
	app.getSerialComm().addSensor(app.getSensorManager().getButtonByName("Btn2"));

	app.getSerialComm().addOtherValue(hellig, "Pot:");
	app.getSerialComm().addOtherStuff(Nachricht);
}

void createSensors() {
	app.getSensorManager().createButton(8, "Btn1");
	app.getSensorManager().createButton(9, "Btn2");
}

//void softwareReset() {
//  SRC_GPR5 = 0x0BAD00F1;
//	SCB_AIRCR = 0x05FA0004;
//	while (1);
//}


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


void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	startSerialConnection(true,true);

	digitalWrite(LED_BUILTIN, LOW);

	pinMode(6, INPUT);
	createSensors();

	sensorSends();
	app.getSensorManager().getButtonByName("Btn1")->update();
	while(app.getSensorManager().getButtonByName("Btn1")->isPressed()) {
		app.getSensorManager().getButtonByName("Btn1")->update();
		app.getSerialComm().sendOneTimeData();
	}
	

	//app.getOutputManager().createMotor(21, 22, 10, "frontLeft");
	//app.getOutputManager().createMotor(32, 33, 11, "back");
	//app.getOutputManager().createMotor(36, 38, 12, "frontRight");
	
	
	//Motor* motor1 = app.getOutputManager().getMotorByName("frontLeft");
	//Motor* motor2 = app.getOutputManager().getMotorByName("back");
	//Motor* motor3 = app.getOutputManager().getMotorByName("frontRight");
	//app.getDrivingControl().addMotor(1, motor1);
	//app.getDrivingControl().addMotor(2, motor2);
	//app.getDrivingControl().addMotor(3, motor3);
	
	//app.getDrivingControl().drive(-90, 0.4, 0);
	//delay(500);
	//app.getDrivingControl().drive(-90, 0.2, 0);
}

void loop() {
	hellig = analogRead(6);
	app.getSensorList().updateAllSensors();
	app.getSerialComm().sendRepeatingData();
	if(Serial.available() > 0) {
		Nachricht = Serial.readString();
	}
}
