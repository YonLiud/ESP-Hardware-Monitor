#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Fonts/Org_01.h>
#include "display.h"
#include "images.h"

#define SDA_PIN 16
#define SCK_PIN 15

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

struct Grid {
  int rows = 2;
  int rowHeight = 40;

  void init(int r) {
    rows = r;
    rowHeight = TFT_HEIGHT / rows;
  }

  int y(int rowIndex) {
    return rowIndex * rowHeight;
  }
};

Grid grid;

void initGrid(int rows) {
  grid.init(rows);
  tft.println("Grid config: " + String(rows));
}

void initDisplay() {
  tft.init(TFT_WIDTH, TFT_HEIGHT);
  clearDisplay();
  tft.setRotation(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.println("Hello ESP32");
}

void showMessage(const char* message){
  tft.println(message);
}

void addText(const char* message){
  tft.print(message);
}

void clearDisplay()
{
  tft.fillScreen(ST77XX_BLACK);
}

void showRow(const char* title, const char* temp, int row) {
  int yStart = grid.y(row);
  int rowHeight = TFT_HEIGHT / grid.rows;

  // Clear this row only
  tft.fillRect(0, yStart, TFT_WIDTH, rowHeight, ST77XX_BLACK);

  // Optional separator
  if (row > 0) {
    tft.drawFastHLine(0, yStart, TFT_WIDTH, ST77XX_WHITE);
  }

  // --- Title ---
  tft.setTextSize(4);
  tft.setTextColor(ST77XX_WHITE);
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);
  int titleX = (TFT_WIDTH - w) / 2;
  int titleY = yStart + rowHeight - h - 5;

  tft.setCursor(titleX, titleY);
  tft.print(title);

  // --- Temp ---
  int tempVal = atoi(temp);
  uint16_t color = ST77XX_GREEN;
  if (tempVal >= 80) color = ST77XX_RED;
  else if (tempVal >= 60) color = ST77XX_YELLOW;

  // Dynamic size: fewer rows → bigger text
  int tempSize = (grid.rows <= 2) ? 9 : (grid.rows == 3 ? 6 : 3);

  tft.setTextSize(tempSize);
  tft.setTextColor(color);

  char buffer[8];
  sprintf(buffer, "%d", tempVal);

  tft.getTextBounds(buffer, 0, 0, &x1, &y1, &w, &h);
  int tempX = (TFT_WIDTH - w) / 2;
  int tempY = titleY - h - 5;

  tft.setCursor(tempX, tempY);
  tft.print(buffer);
}
