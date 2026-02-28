#pragma once
#include "Sensorik/SensorBase/SensorBase.h"

// Used to read if a button is pressed or not. 
// The buttons must be connected to plus and don't need an external pulldown resistor.
class Button : public SensorBase {
private:
public:
	Button (int p,String n);
	void update() override;
	float rawData() override;
	bool isPressed() const;
};