#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Outputs/OutputBase/Outputs.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

class Ssd1306 : public OutputBase {
private:
	Adafruit_SSD1306* display;
public:
	Ssd1306(String n);
	void print(float v1, float v2, float v3);
	void clear();
};
