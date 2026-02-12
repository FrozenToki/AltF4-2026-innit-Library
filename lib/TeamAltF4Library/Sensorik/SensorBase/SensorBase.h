#pragma once
#include <Arduino.h>

// Used to create all
class SensorBase {
protected:
	int pin;
	float value;
	String name;
	String type;
private:
	static int sensorCount;
public:
	SensorBase(int p,String n);

  static String BUTTON;
	static String BNO055;


	int getPin() const;
	String getName() const;
	String getType() const;

	int& getPinRef();
	String& getNameRef();


	virtual void update() = 0;
	virtual float rawData() = 0;
	
	// Updates the sensor and returns its raw data.
	float readSensor();

	SensorBase();
};





