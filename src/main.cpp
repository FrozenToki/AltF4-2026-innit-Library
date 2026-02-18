#include <Arduino.h>
#include "app/Application.h"    
#include "Sensorik/SensorBase/SensorBase.h"
#include "Config/Config.h"
#include "Outputs/OutputBase/Motor/Motor.h"
//#include "Sensorik/SensorBase/Bno055/Bno055.h"

Application app;

Bno055* bno;

Button* greenBtn;


//Ssd1306* display;
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

	app.getSensorManager().createButton(6, "GreenButton");
	greenBtn = app.getSensorManager().getButtonByName("GreenButton");

	//display = app.getOutputManager().getSsd1306ByName("Display");



	pinMode(18, INPUT);
	
	
	while(!greenBtn->isPressed()) {
		bno->getCalibrationStatus();
		//display->print(bno->getSystem(), bno->getGyro(), bno->getAccel());
		delay(100);
		greenBtn->update();
	}
	//display->clear();

}

float degree = 0;
float strength = 0;

float i = 0;
void loop() {	
	digitalWrite(LED_BUILTIN, LOW);
	if (Serial3.available())  {
		//Serial.println(Serial3.readStringUntil('\n'));
		String input = Serial3.readStringUntil('\n');
		sscanf(input.c_str(), "%f;%f", &degree, &strength);


		while (degree > 180) degree -= 360;
		while (degree < -180) degree += 360;	
	}
	
	app.getIrSensorReader().readAll(30000, false, 0);
	app.getIrSensorReader().setAll();

	IrSensor* ir1 = app.getSensorManager().getIrSensorByName("ir1");
	IrSensor* ir2 = app.getSensorManager().getIrSensorByName("ir2");
	
	float v1 = ir1->getCalculatedValue();
	float v2 = ir2->getCalculatedValue();

	float ir = (v1 + v2) / 2;
	if(digitalRead(9)== HIGH) {
		bno->update();
		
		app.getModi().mode(degree, strength, ir);
		
	} 
	else {
		greenBtn->update();
		if(greenBtn->isPressed()) {
			app.getModi().setKickOffMode();
			bno->calibrate();
		}
		
		app.getDrivingControl().turnOff();
		//display->print(distLeft->rawData(),distBack->rawData(),distRight->rawData());

	}
	app.getLoops().readDistance();
	


}

