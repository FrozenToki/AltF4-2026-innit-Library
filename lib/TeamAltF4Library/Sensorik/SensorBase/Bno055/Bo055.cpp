#include "Bno055.h"

Bno055::Bno055(int p, String n) : SensorBase(p, n) {
	type = BNO055;
	bno = Adafruit_BNO055(55, 0x28, &Wire2);
	Wire2.begin();
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
}

void Bno055::update() {
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  value = euler.x(); 
}

float Bno055::rawData() {
	return value;
}
