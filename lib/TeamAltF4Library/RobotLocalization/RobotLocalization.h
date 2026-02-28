#pragma once 
#include <Arduino.h>


class Application; 

class RobotLocalization {
private:
	Application* app;

public:
	RobotLocalization(Application* a);
};