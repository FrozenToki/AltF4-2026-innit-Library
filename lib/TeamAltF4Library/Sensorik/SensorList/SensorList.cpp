#include "SensorList.h"
#include "app/Application.h"

SensorList::SensorList(Application* a) : app(a) {}

SensorBase* SensorList::sensorList[Config::MAX_SENSORS] = {nullptr};
int SensorList::sensorCount = 0;

void SensorList::addSensor(SensorBase* s) {
	for (int i = 0; i < sensorCount; i++) {
		if (sensorList[i]->getName() == s->getName()) {
			Serial.println("Sensorname existiert schon!");
			return;
		}
	}

	if (sensorCount < Config::MAX_SENSORS) {
		sensorList[sensorCount++] = s;
	}
}

SensorBase* SensorList::getSensorByName(const String& n) {
	for (int i = 0; i < sensorCount; i++) {
		if (sensorList[i]->getName() == n) {
			return sensorList[i];
		}
	}
	return nullptr;
}

void SensorList::updateAllSensors() {
	for (int i = 0; i < sensorCount; i++) {
		sensorList[i]->update();
	}
}