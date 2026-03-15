#include "Ssd1306.h"

Ssd1306::Ssd1306(String n) : OutputBase(n) {
	display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

	Wire1.begin();
	display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

	display->clearDisplay();
	display->setTextColor(SSD1306_WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println("TeamAlt+F4");
	display->display();

}

void Ssd1306::print(float v1, float v2, float v3) {
	display->clearDisplay();
	
	display->setCursor(0, 0);
	display->println(v1);
	
	display->setCursor(0, 20);
	display->println(v2);
	
	display->setCursor(0, 40);
	display->println(v3);
	
	display->display();
}

void Ssd1306::print(String v1, String v2, String v3) {
	display->clearDisplay();
	
	display->setCursor(0, 0);
	display->println(v1);
	
	display->setCursor(0, 20);
	display->println(v2);
	
	display->setCursor(0, 40);
	display->println(v3);
	
	display->display();
}

void Ssd1306::resetConnection() {
	display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

	display->clearDisplay();
	display->setTextColor(SSD1306_WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println("TeamAlt+F4");
	display->display();
}

void Ssd1306::clear() {
	display->clearDisplay();
	display->display();
}
