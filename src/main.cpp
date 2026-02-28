#include <Arduino.h>
#include "app/Application.h"    
#include "Config/Config.h"

Application app;

Bno055* bno;

Ssd1306* display;

ButtonCross* buttonC;


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
	//display->print("_______", "In Mode1", "_______");
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



void setup() {
	display = app.getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);
	bno = app.getSensorManager().getBno055ByName(Config::GYRO_NAME);
	buttonC = app.getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);

	app.getMenuManager().addMenuItem("Game Mode", modeOne);
	app.getMenuManager().addMenuItem("Mode2", modeTwo);
	app.getMenuManager().addMenuItem("Gyro Calib", modeThree);

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

