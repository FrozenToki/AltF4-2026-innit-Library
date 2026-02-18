#include "Bno055.h"

Bno055::Bno055(int p, String n) : SensorBase(p, n) {
	type = BNO055;
	bno = Adafruit_BNO055(55, 0x28, &Wire1);
	Wire1.begin();
if (!bno.begin()) {
	while (true) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
	
}
	bno.setExtCrystalUse(true);
	delay(100);
	bno.setMode(OPERATION_MODE_IMUPLUS);
	values.resize(5);
	for (size_t i = 0; i < 5; i++) {
		values[i] = 0.0f;
	}
	
}


void Bno055::update() {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    float raw = euler.x();  


		raw -= calibratedValue;
		if (raw < 0) raw += 360;
		if (raw >= 360) raw -= 360;
    
    value = raw;


    float diff = raw - lastAngle;

    if (diff > 180)  diff -= 360;
    if (diff < -180) diff += 360;

    continuousAngle += diff;
    lastAngle = raw;


    values.erase(values.begin());
    values.push_back(raw);
}




float Bno055::rawData() {
    float sum = 0;
    for (float v : values) sum += v;
    return sum / values.size();
}

void Bno055::calibrate() {
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  calibratedValue = euler.x();
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
