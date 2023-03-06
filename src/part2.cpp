/**
 * @file part1.cpp
 * @brief SOFTWARE SPI
 * @date 2023-03-05
 */

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Adafruit_CAP1188.h>

#define CAP1188_CLK 25
#define CAP1188_MISO 27
#define CAP1188_MOSI 26
#define CAP1188_CS 33
#define CAP1188_RESET -1

Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, -1);
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

  const char* title = "Part 2";

  header(title);

  tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.setTextDatum(TL_DATUM); 
  tft.setTextPadding(0); // Setting to zero switches off padding

  uint8_t touched = cap.touched();
  uint8_t counter = 0;

  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      counter++;
    }
  }
  
  yield(); tft.drawNumber(counter, x, y, font);
  // delay(50);
}

