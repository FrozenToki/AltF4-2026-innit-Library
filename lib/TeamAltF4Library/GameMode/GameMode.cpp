#include "GameMode.h"
#include "app/Application.h"

GameMode::GameMode(Application *a) : app(a) {

	motor1 = app->getOutputManager().getMotorByName(Config::MOTOR_VL_NAME);
	motor2 = app->getOutputManager().getMotorByName(Config::MOTOR_BA_NAME);
	motor3 = app->getOutputManager().getMotorByName(Config::MOTOR_VR_NAME);
	app->getDrivingControl().addMotor(1, motor1);
	app->getDrivingControl().addMotor(2, motor2);
	app->getDrivingControl().addMotor(3, motor3);

	distRight = app->getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);
	distLeft = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	distBack = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);
	
	ring = app->getSensorManager().getIrRingByName(Config::IR_RING_NAME);
	
	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME); 

	greenBtn = app->getSensorManager().getButtonByName(Config::GREEN_BUTTON_NAME);

	display = app->getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);

	buttonCross = app->getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);
}

void GameMode::loop() {
	ring->update();

	degree = ring->getAngle();
	strength = ring->getStrength();

	while (degree > 180) degree -= 360;
	while (degree < -180) degree += 360;	
	
	app->getIrSensorReader().readAll(30000, false, 0);
	app->getIrSensorReader().setAll();

	float ir = 30 / 2;
	if(digitalRead(9)== HIGH) {
		bno->update();
		
		app->getModi().mode(degree, strength, ir);
		
		//app->getDrivingControl().drive(0, 0.5, app->getRotationControl().getRotation(degree + bno->rawData()));
		display->print("___",app->getModi().getLastMode(), "___");
		
	} 
	else {
		buttonCross->update();
		if(buttonCross->pressed(0)) {
			app->getModi().setKickOffMode();
			bno->calibrate();
		}
		
		app->getDrivingControl().turnOff();
		buttonCross->update();
		display->print(buttonCross->pressed(3), buttonCross->rawData() ,0);

	}
	app->getLoops().readDistance();
	
	//display->print(bno->getContinuousAngle(), app->getRotationControl().getRotation(-90), strength);
}
