#include "Bno055.h"

Bno055::Bno055(int p, String n) : SensorBase(p, n) {
	type = BNO055;
	bno = Adafruit_BNO055(55, 0x28, &Wire2);
	Wire2.begin() ;
	Wire2.setClock(10000);

	if (!bno.begin(OPERATION_MODE_IMUPLUS)) {
		//while (true) {
		//	digitalWrite(LED_BUILTIN, HIGH);
		//	delay(100);
		//	digitalWrite(LED_BUILTIN, LOW);
		//	delay(100);
		//}
		delay(1000);
		
	}

	
	Wire2.setTimeout(10);
	bno.setExtCrystalUse(true);
	delay(100);

	delay(10);
}


void Bno055::update() {
	sensors_event_t event;

	if(!bno.getEvent(&event, Adafruit_BNO055::VECTOR_EULER)){
    return;
	}

	//imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

	
	
	float raw;
	raw = event.orientation.x;

	
	//if (isnan(euler.x())) {
	//	return;
	//}
	//else {
	//	raw = euler.x();  
	//}

	

	

	
	raw -= calibratedValue;
	if (raw < 0) raw += 360;
	if (raw >= 360) raw -= 360;

	
	float diff = raw - lastAngle;

	if (diff > 180)  diff -= 360;
	if (diff < -180) diff += 360;

	//if (abs(diff) > 90) {
  //  return;
	//}

	continuousAngle += diff;
	lastAngle = raw;



	value = raw;


}





float Bno055::rawData() {

	return value;	
}

void Bno055::calibrate() {
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	calibratedValue = euler.x();

	lastAngle = 0;
	continuousAngle = 0.0f;


}

void Bno055::getCalibrationStatus() {
	bno.getCalibration(&system, &gyro, &accel, &mag);
}

uint8_t Bno055::getSystem() {
	return system;
}

uint8_t Bno055::getGyro() {
	return gyro;
}

uint8_t Bno055::getAccel(){
	return accel;
}


float Bno055::getContinuousAngle() {
    return continuousAngle;
}
