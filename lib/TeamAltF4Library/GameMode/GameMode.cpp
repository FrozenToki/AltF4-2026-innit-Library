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
	distLeft  = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	distBack  = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);
	
	ring = app->getSensorManager().getIrRingByName(Config::IR_RING_NAME);
	
	bno = app->getSensorManager().getBno055ByName(Config::GYRO_NAME); 

	greenBtn = app->getSensorManager().getButtonByName(Config::GREEN_BUTTON_NAME);

	display = app->getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);

	buttonCross = app->getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);
}

void GameMode::loop() {
	
	// Infrarot Sensoren lesen
	ring->update();

	// Position des Balles
	degree = app->getGeometry().normalizeAngle(ring->getAngle());
	strength = ring->getStrength();

  // Ballhalter Sensoren lesen
	app->getIrSensorReader().readAll(30000, false, 0);
	app->getIrSensorReader().setAll();

	// Gyro Sensor
	bno->update();

	// Abstandssensoren lesen
  app->getLoops().readDistance();

	// Hauptschalter
	if(digitalRead(9)== HIGH) {
		
		app->getModi().mode(degree, strength);
		display->print("___",app->getModi().getLastMode(), "___");
		
	} 
	else {

		buttonCross->update();
		if(buttonCross->pressed(2)) {
			while (buttonCross->pressed(2)) {
				buttonCross->update();
			}
			app->getModi().setKickOffMode();
			// GryoSensor kalibrieren
			bno->calibrate();
		}
		
		app->getDrivingControl().turnOff();
		buttonCross->update();
		display->print(app->getGeometry().normalizeAngle(bno->rawData()), app->getStates().robotState() ,distLeft->rawData());

	}
	
	
	//display->print(bno->getContinuousAngle(), app->getRotationControl().getRotation(-90), strength);
}
