#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

void initDisplay(bool inverted);
void showMessage(const char* message);
void clearDisplay();
void showTemp(const char* temp);
void showTitle(const char* title);
void drawImage(const unsigned char* image);

#endif
