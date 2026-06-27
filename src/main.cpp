#include <Arduino.h>
#include "app/ApplicationInnit.h"    
#include "Config/Config.h"
#include "MovingAverage/MovingAverage.h"
#include "GameMode/GameMode.h"

ApplicationInnit app;
GameMode game(&app);



Bno055* bno;
Ssd1306* display;
ButtonCross* buttonC;
IrRing* ring;

Motor* motor1;
Motor* motor2;
Motor* motor3;

Sr04* distLeft;
Sr04* distBack;
Sr04* distRight;


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
	game.loop();	
}

void modeThree() {
	bno->getCalibrationStatus();
	display->print(bno->getSystem(), bno->getGyro(), bno->getAccel());
	delay(100);
}

void irSensorCalibration() {
	app.getCalibration().calibrateIrSensors();
}


void testDistanceBall() {
	ring->update();

	float ringStrenght = ring->getStrength() * 8;
 
	float distanceRaw = ((1/sqrt(ringStrenght)) * 2000);
	float distance = (distanceRaw -  65)*2;
	display->print(distance, 0 ,ring->getStrength());

	app.getDrivingControl().drive(0, 0.5, 0);
}

void ringe() {
	app.getCalibration().calibrateIrRing();
}


void setup() {

	motor1 = app.getOutputManager().getMotorByName(Config::MOTOR_VL_NAME);
	motor2 = app.getOutputManager().getMotorByName(Config::MOTOR_BA_NAME);
	motor3 = app.getOutputManager().getMotorByName(Config::MOTOR_VR_NAME);

	display = app.getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);
	bno = app.getSensorManager().getBno055ByName(Config::GYRO_NAME);
	buttonC = app.getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);
	ring = app.getSensorManager().getIrRingByName(Config::IR_RING_NAME);

	distLeft = app.getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	distBack = app.getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);
	distRight = app.getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);

	
	
	app.getMenuManager().addMenuItem("Game Mode", modeOne);
	app.getMenuManager().addMenuItem("Gyro Calib", modeThree);
	app.getMenuManager().addMenuItem("IrCalib", irSensorCalibration);
	app.getMenuManager().addMenuItem("testDist", testDistanceBall);
	app.getMenuManager().addMenuItem("ringCalib", ringe);

	

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

