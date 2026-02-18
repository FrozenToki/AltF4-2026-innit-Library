#pragma once
#include <Arduino.h>
#include "Sensorik/SensorBase/SensorBase.h"
#include "Sensorik/SensorManager/SensorManager.h"
#include "Sensorik/SensorList/SensorList.h"
#include "Outputs/OutputManager/OutputManger.h"
#include "Outputs/OutputList/OutputList.h"
#include "Config/Config.h"
#include "Debugging/Errors/ErrorMessages.h"
#include "Driving/drivingControl/DrivingControl.h"
#include "Serial/SerialComm.h"
#include "Driving/rotationControl/RotationControl.h"
#include "Geometrie/Geometrie.h"
#include "loops/loops.h"
#include "Modi/Modi.h"
#include "Sensorik/IrSensorReader/IrSensorReader.h"

// Used to get acces to all the parts of the library from anywhere in the programm.
// It has instances of all the different main parts of the library.
class Application {
private:
	SensorManager sensorManager;
	SensorList sensorList;

	OutputManager outputManager;
	OutputList outputList;

	Config config;

	ErrorMessages errorMessages;

	DrivingControl drivingControl;
	RotationControl rotationControl;

	SerialComm serialComm;

	Geometrie geometrie;

	Loops loops;

	Modi modi;

	IrSensorReader irSensorReader;
public:
	SensorList& getSensorList();
	SensorManager& getSensorManager();
	
	OutputList& getOutputList();
	OutputManager& getOutputManager();

	Config& getConfig();

	ErrorMessages& getErrorMessage();

	DrivingControl& getDrivingControl();
	RotationControl& getRotationControl();

	SerialComm& getSerialComm();

	Geometrie& getGeometrie();

	Loops& getLoops();

  Modi& getModi();

	IrSensorReader& getIrSensorReader();

	Application();

};
	
