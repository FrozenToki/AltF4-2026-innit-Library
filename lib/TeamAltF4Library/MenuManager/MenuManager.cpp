#include "MenuManager.h"
#include "app/Application.h"

MenuManager::MenuManager(Application *a) : app(a) {
	buttonCross = app->getSensorManager().getButtonCrossByName(Config::BUTTON_CROSS_NAME);

	display = app->getOutputManager().getSsd1306ByName(Config::DISPLAY_NAME);

	greenButton = app->getSensorManager().getButtonByName(Config::GREEN_BUTTON_NAME);

	modes.reserve(10);
	modeNames.reserve(10);
}

void MenuManager::addMenuItem(String n, void (*mode)()) {
	modes.push_back(mode);
	modeNames.push_back(n);
}

void MenuManager::loop() {
	
	if (inMode) {
		greenButton->update();
		if (greenButton->isPressed()) {
			
			app->getDrivingControl().turnOff();
			inMode = false;
		} else {
			modes[mode]();
		}
		
		
	} else {
		buttonCross->update();
		if  (buttonCross->pressed(4)) {
			while (buttonCross->pressed(4)){
				buttonCross->update();
			}
			display->resetConnection();
		}
		else if (buttonCross->pressed(1)) {
			while (buttonCross->pressed(1)){
				buttonCross->update();
			}
			if (mode == 0) {
				mode = modes.size() - 1;
			}
			else {
				mode -= 1;
			}
			
		}
		else if (buttonCross->pressed(3)) {
			while (buttonCross->pressed(3)){
				buttonCross->update();
			}
			mode += 1;
		}


		if (mode == modes.size()) {
			mode = 0;
		}

		display->print("_______", modeNames[mode], "_______");
		if (buttonCross->pressed(2)) {
			while (buttonCross->pressed(2)){
				buttonCross->update();
			}
			inMode = true;
		}
	}
}
