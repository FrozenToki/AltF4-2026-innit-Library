#include <Global.h>
#include <Arduino.h>
#include "app/Application.h"    //"app/Application.h"
#include "Sensorik/SensorBase/SensorBase.h"
#include "Config/Config.h"
#include "Outputs/OutputBase/Motor/Motor.h"

String errorMessage = "Alles ok";

Application app;


//SerialComm comm(Serial); 

//void SensorSends(){
    

//    comm.addOtherValue(ButtonCount, "BtnCnt:");

//    comm.addOtherStuff(errorMessage);
//    comm.addOtherStuff(loopCount); 
//    comm.addOtherStuff(loopTime); 
//    comm.addOtherStuff(loopPerSec);
//    comm.addOtherStuff(btnPresses);
//}


void softwareReset() {
    SRC_GPR5 = 0x0BAD00F1;
	SCB_AIRCR = 0x05FA0004;
	while (1) ;
}


void startSerialConnection(bool baudRate, bool waitForConnection) {
	if(baudRate){
		Serial.begin(115200);
	}
	else{
		Serial.begin(9600);
	}
	
	if(waitForConnection){
		#if defined(USBCON) || defined(TEENSYDUINO)
		while (!Serial);
		#endif
	}
	delay(200);
}

bool receivedConfirm = false;




void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // LED Pin als Ausgang setzen
	digitalWrite(LED_BUILTIN, HIGH);
	//startSerialConnection(true,true);

	digitalWrite(LED_BUILTIN, LOW);

	app.getOutputManager().createMotor(32, 33, 11, "frontLeft");
	app.getOutputManager().getMotorByName("frontLeft")->turnOn(50, Config::FORWARDS);
	delay(500);
	app.getOutputManager().getMotorByName("frontLeft")->turnOn(50, Config::BACKWARDS);

	// Motor frontLeft(32, 33, 11, "frontLeft");
	// frontLeft.turnOn(100, Config::FORWARDS);
}

unsigned long rane = 2;
int rans = 0;
/**
 *  @deprecated
 */ 
bool btnPressed = false;

void loop() {


}
