#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_ST7789.h>

#define TFT_CS     18
#define TFT_DC     17
#define TFT_RST    16
#define TFT_SCLK   41
#define TFT_MOSI   40

#define TFT_HEIGHT  320
#define TFT_WIDTH   240

void initDisplay();
void showMessage(const char* message);
void clearDisplay();
void initGrid(int rows);
void showRow(const char* title, const char* temp, int row);
void drawImage(const unsigned char* image);

#endif
