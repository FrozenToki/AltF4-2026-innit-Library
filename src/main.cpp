#include <Arduino.h>
#include "app/Application.h"    
#include "Config/Config.h"
#include "MovingAverage/MovingAverage.h"

Application app;

Bno055* bno;
Ssd1306* display;
ButtonCross* buttonC;
IrRing* ring;

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

void modeOne() {
	app.getGameMode().loop();	
}

void modeTwo() {
	//display->print("_______", "In Mode2", "_______");
	display->print(0, app.getStates().getBallInHolderThreshould(), 0);
	buttonC->update();
	if (buttonC->pressed(0)) {
		app.getStates().setBallInHolderThreshould(18000);
	}
	else if (buttonC->pressed(1)) {
		app.getStates().setBallInHolderThreshould(16000);
	}
}

void modeThree() {
	bno->getCalibrationStatus();
	display->print(bno->getSystem(), bno->getGyro(), bno->getAccel());
	delay(100);
}

void modeFour() {
	
	bno->update();

	ring->update();

	float degree = ring->getAngle();

	display->print(0,0,degree);


	while (degree > 180) degree -= 360;
	while (degree < -180) degree += 360;	
	
	float speed;

	if (degree < 25 && degree > -25) {
		speed = Config::MIDDLE_SPEED;
	}
	else {
		speed = 0;
	}
	
	float direction = degree + bno->rawData();
	float angle = 0;

	app.getDrivingControl().drive(angle, speed, app.getRotationControl().getRotation(direction));
		
}


void setup() {


	display = app.getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);
	bno = app.getSensorManager().getBno055ByName(Config::GYRO_NAME);
	buttonC = app.getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);
	ring = app.getSensorManager().getIrRingByName(Config::IR_RING_NAME);

	app.getMenuManager().addMenuItem("Game Mode", modeOne);
	app.getMenuManager().addMenuItem("Mode2", modeTwo);
	app.getMenuManager().addMenuItem("Gyro Calib", modeThree);
	app.getMenuManager().addMenuItem("test", modeFour);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	//startSerialConnection(true,true);
	
	//digitalWrite(LED_BUILTIN, LOW);
	pinMode(18, INPUT);
	pinMode(9, INPUT_PULLDOWN);
	

	display->clear();

}



float i = 0;
void loop() {	
	app.getMenuManager().loop();
}

