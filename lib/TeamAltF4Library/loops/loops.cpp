#include "loops.h"
#include "app/Application.h"


Loops::Loops (Application* a) : app(a) {
	distRight = app->getSensorManager().getSr04ByName("distRight");
	distBack = app->getSensorManager().getSr04ByName("distBack");
	distLeft = app->getSensorManager().getSr04ByName("distLeft");
	
}

void Loops::readDistance() {
	if (millis() - time >= 25 )
	{
		time = millis();
		if (status == 0)
		{
			distRight->update();
			status = 1;
		}
		else if (status == 1) {
			distBack->update();
			status = 2;
		}
		else {
			distLeft->update();
			status = 0;
		}
	}
	
}
