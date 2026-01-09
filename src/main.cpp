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

	app.getOutputManager().createMotor(21, 22, 10, "frontLeft");
	app.getOutputManager().createMotor(32, 33, 11, "back");
	app.getOutputManager().createMotor(36, 38, 12, "frontRight");
	
	
	Motor* motor1 = app.getOutputManager().getMotorByName("frontLeft");
	Motor* motor2 = app.getOutputManager().getMotorByName("back");
	Motor* motor3 = app.getOutputManager().getMotorByName("frontRight");
	app.getDrivingControl().addMotor(1, motor1);
	app.getDrivingControl().addMotor(2, motor2);
	app.getDrivingControl().addMotor(3, motor3);
	

	
	
	app.getDrivingControl().drive(-90, 0.4, 0);
	delay(500);
	app.getDrivingControl().drive(-90, 0.2, 0);


	

}

unsigned long rane = 2;
int rans = 0;
/**
 *  @deprecated
 */ 
bool btnPressed = false;

void loop() {


}
