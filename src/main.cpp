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
SerialReciever* ring;

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

	float ringStrenght = ring->getValue(2) * 8;
 
	float distanceRaw = ((1/sqrt(ringStrenght)) * 2000);
	float distance = (distanceRaw -  65)*2;
	display->print(distance, 0 ,ringStrenght);

	app.getDrivingControl().drive(0, 0.5, 0);
}

void ringe() {
	app.getCalibration().calibrateIrRing();
}


void setup() {

	bno = app.getSensorManager().createBno055(255, Config::GYRO_NAME);
	
	distRight = app.getSensorManager().createSr04(5,4,Config::RIGHT_DIST_NAME);
	distLeft = app.getSensorManager().createSr04(29, 28, Config::LEFT_DIST_NAME);
	distBack = app.getSensorManager().createSr04(27, 26, Config::BACK_DIST_NAME);

	app.getSensorManager().createIrSensor(2, Config::IR_SENS_LEFT_NAME, 0.0f);
	app.getSensorManager().createIrSensor(3, Config::IR_SENS_RIGHT_NAME, 0.0f);

	ring = app.getSensorManager().createSerialReciever(&Serial3, Config::IR_RING_NAME);

	buttonC = app.getSensorManager().createButtonCross(Config::BUTTON_CROSS_NAME, 18, 924, 508, 834, 317, 691);

	app.getSensorManager().createButton(6, Config::GREEN_BUTTON_NAME);

	app.getSensorManager().createEZ(39,Config::EZ_VL_NAME);
	app.getSensorManager().createEZ(40,Config::EZ_V_NAME);
	app.getSensorManager().createEZ(41,Config::EZ_VR_NAME);

	display = app.getOutputManager().createSsd1306(Config::DISPLAY_NAME);

	motor1 = app.getOutputManager().createMotor(21, 30, 10, 20, Config::MOTOR_VL_NAME, false);
	motor2 = app.getOutputManager().createMotor(32, 33, 11, 22, Config::MOTOR_BA_NAME);
	motor3 =app.getOutputManager().createMotor(36, 38, 12, 23, Config::MOTOR_VR_NAME);

	
	
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

