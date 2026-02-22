#include "loops.h"
#include "app/Application.h"


Loops::Loops (Application* a) : app(a) {
	distRight = app->getSensorManager().getSr04ByName(Config::RIGHT_DIST_NAME);
	distBack = app->getSensorManager().getSr04ByName(Config::BACK_DIST_NAME);
	distLeft = app->getSensorManager().getSr04ByName(Config::LEFT_DIST_NAME);
	
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
