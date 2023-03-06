/**
 * @file part1.cpp
 * @brief I2C COMMUNICATION
 * @date 2023-03-05
 */

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Adafruit_CAP1188.h>
Adafruit_CAP1188 cap = Adafruit_CAP1188();
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(9600);
  Serial.println("CAP1188 test!");
  
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void header(const char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(string, 35, 10, 4);
 
}

void loop() {
  int x = 0;
  int y = 60;
  byte font = 8;

  const char* title = "Part 1";

  header(title);

  tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.setTextDatum(TL_DATUM); 
  tft.setTextPadding(0);

  uint8_t touched = cap.touched();
  uint8_t counter = 0;

  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      counter++;
    }
  }
  
  yield(); tft.drawNumber(counter, x, y, font);
}
