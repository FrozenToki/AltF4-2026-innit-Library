#pragma once
#include <Arduino.h>

class Application; 

class Geometrie {
private:
	Application* app;
public: 
	Geometrie(Application* a);
	float normalizeAngle(float angle);
};