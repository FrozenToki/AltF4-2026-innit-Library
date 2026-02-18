#include "Sr04.h"

Sr04::Sr04(int pinT, int pinE, String n) : SensorBase(0, n), pinTrig(pinT), pinEcho(pinE) {
	pinMode(pinTrig, OUTPUT);
	pinMode(pinEcho, INPUT);
}

void Sr04::update()	{
	digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
 
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

	long duration = pulseIn(pinEcho, HIGH, 30000);

    if (duration == 0) {
        value = 1000;  
    } else {
        value = duration * 0.0343 / 2.0;
    }
	
	if (value >= 1000)
	{
		value = -1;
	}
	
}

float Sr04::rawData() {
	return value;
}


