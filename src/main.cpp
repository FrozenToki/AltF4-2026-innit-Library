#include <Arduino.h>
#include "app/Application.h"    
#include "Config/Config.h"
#include "MovingAverage/MovingAverage.h"

Application app;

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
float motor1SpeedFactor = 1;

void modeFour() {

	motor1->updateAmperUsage();
	motor2->updateAmperUsage();
	motor3->updateAmperUsage();

	if (motor1->getAmperUsage() > 1) {
		if (motor1SpeedFactor <= 0) {
			motor1SpeedFactor = 0;
		}
		else {
			motor1SpeedFactor -= 0.02;
		}
	}
	else {
		if (motor1SpeedFactor >= 1) {
			motor1SpeedFactor = 1;
		}
		else {
			motor1SpeedFactor += 0.02;
		}
		
	}

	motor1->turnOn(Config::HIGH_SPEED * motor1SpeedFactor);
	//motor2->turnOn(0.9);
	//motor3->turnOn(0.9);
	

	

	display->print(motor1->getAmperUsage(), 0, Config::HIGH_SPEED * motor1SpeedFactor);
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

void technical() {
	while (distBack->rawData() >= 15)
	{
		app.getLoops().readDistance();

		bno->update();

		if (distLeft->rawData() <= 8		)
		{
			app.getDrivingControl().drive(175, Config::MIDDLE_SPEED, app.getRotationControl().getRotation(0));
		}
		else {
			app.getDrivingControl().drive(-160, Config::MIDDLE_SPEED, app.getRotationControl().getRotation(0));
		}
	}

	
	while (!app.getStates().ballState() == Config::BALL_HELD) {
		app.getIrSensorReader().readAll(30000, false, 0);
		app.getIrSensorReader().setAll();
		ring->update();
		app.getDrivingControl().drive(0, 0.3, app.getRotationControl().getRotation(ring->getAngle()));
	
	
	}
	int time = millis();
	while (millis() - time < 800)
	{
		display->print(ring->getAngle(),0,0);
		app.getDrivingControl().drive(90, Config::LOW_SPEED, app.getRotationControl().getRotation(0));
		ring->update();
		bno->update();
		
	}
	bno->calibrate();

	while (millis() - time < 10000)
	{
		modeOne();
	}

	app.getDrivingControl().drive(90, Config::LOW_SPEED, app.getRotationControl().getRotation(0));
	delay(100);
	app.getDrivingControl().drive(0, Config::LOW_SPEED, app.getRotationControl().getRotation(0));
	
	
	delay(1000000);
	
}



void superTeam() {
	
	display->print(analogRead(39), analogRead(40), 0); 

	if(digitalRead(9)== HIGH) {
		
	ring->update();
	bno->update();
	float speed = Config::LOW_SPEED;
	float angle = ring->getAngle();
	

	if (analogRead(39) >= 1008 && analogRead(40) >= 1003) {
		angle = app.getGeometry().normalizeAngle(angle);
		angle = 180 - angle;
		angle = app.getGeometry().normalizeAngle(angle);
		speed = Config::MIDDLE_SPEED;
	}
	else if (analogRead(39) >= 1008) {
		angle = angle + 180;
		angle = app.getGeometry().normalizeAngle(angle);
		speed = Config::MIDDLE_SPEED;
	}
	else if (analogRead(40) >= 1003) {
		angle = angle + 180;
		angle = app.getGeometry().normalizeAngle(angle);
		speed = Config::MIDDLE_SPEED;
	}
	if (angle < 200 && angle > 160) {
		angle = 235;
	}
	else if (angle > -200 && angle < -160) {
		angle = -235;
	}
	app.getDrivingControl().drive(angle, speed, app.getRotationControl().getRotation(0));
		
	} 
	else {
		app.getDrivingControl().turnOff();
	}
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
	app.getMenuManager().addMenuItem("Mode2", modeTwo);
	app.getMenuManager().addMenuItem("Gyro Calib", modeThree);
	app.getMenuManager().addMenuItem("AMPER TEST", modeFour);
	app.getMenuManager().addMenuItem("IrCalib", irSensorCalibration);
	app.getMenuManager().addMenuItem("testDist", testDistanceBall);
	app.getMenuManager().addMenuItem("ringCalib", ringe);
	app.getMenuManager().addMenuItem("technicalC", technical);
	app.getMenuManager().addMenuItem("superTeam", superTeam);
	

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

