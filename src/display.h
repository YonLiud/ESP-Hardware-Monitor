#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

void initDisplay();
void showMessage(const char* message);
void clearDisplay();
void showTemp(const char* temp);
void showTitle(const char* temp);

#endif
