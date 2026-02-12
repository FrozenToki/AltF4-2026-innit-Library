#include <Arduino.h>
#include "app/Application.h"    
#include "Sensorik/SensorBase/SensorBase.h"
#include "Config/Config.h"
#include "Outputs/OutputBase/Motor/Motor.h"
#include "Sensorik/SensorBase/Bno055/Bno055.h"

Application app;

Bno055* bno;
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
	Serial.println("Connection established");
}

Motor* motor1;
Motor* motor2;
Motor* motor3;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	//startSerialConnection(true,true);
	
	//digitalWrite(LED_BUILTIN, LOW);
	
	
	

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
	bno = app.getSensorManager().getBno055ByName("GyroSensor1"); 
}

float degree = 0;

float i = 0;
void loop() {	
	if (Serial3.available())  {
		//Serial.println(Serial3.readStringUntil('\n'));
		String input = Serial3.readStringUntil('\n');
		degree = input.toFloat();
		while (degree > 180) degree -= 360;
		while (degree < -180) degree += 360;	
	}
	if(digitalRead(9)== HIGH) {
		bno->update();
		app.getDrivingControl().drive(0, 0 , app.getRotationControl().getRotation(0));
		//Serial.println(bno->rawData());
		//Serial.println(app.getRotationControl().getRotation());
	} 
	else {
		motor1->turnOff();
		motor2->turnOff();
		motor3->turnOff();
	}

	//delay(100);

}

