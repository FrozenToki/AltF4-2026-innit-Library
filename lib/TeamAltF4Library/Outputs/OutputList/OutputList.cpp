#include "OutputList.h"
#include "app/Application.h"

OutputList::OutputList(Application* a) : app(a) {}

OutputBase* OutputList::outputList[Config::MAX_OUTPUTS] = {nullptr};
int OutputList::outputCount = 0;

void OutputList::addOutput(OutputBase* s) {
	for (int i = 0; i < outputCount; i++) {
		if (outputList[i]->getName() == s->getName()) {
			Serial.println("Outputname exstiert schon!");
			return;
		}
	}

	if (outputCount < Config::MAX_OUTPUTS) {
		outputList[outputCount++] = s;
	}
}

OutputBase* OutputList::getOutputByName(const String& n) {
	for (int i = 0; i < outputCount; i++) {
		if (outputList[i]->getName() == n) {
			return outputList[i];
		}
	}
	return nullptr;
}