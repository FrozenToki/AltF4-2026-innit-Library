#include "Outputs.h"

OutputBase::OutputBase(String n) : name(n) {}

String OutputBase::LED = "Led";
String OutputBase::MOTOR = "Motor";


String& OutputBase::getNameRef() {
	return name;  
}

String OutputBase::getName() const {
	return name;  
}

String OutputBase::getType() const {
	return type;
}
