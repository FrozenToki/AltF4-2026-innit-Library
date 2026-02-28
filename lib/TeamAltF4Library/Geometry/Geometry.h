#pragma once
#include <Arduino.h>

class Application; 

class Geometry {
private:
	Application* app;
public: 
	Geometry(Application* a);
	float normalizeAngle(float angle);
};