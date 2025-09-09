#include <Arduino.h>
#include <Wire.h>
#include <BS811X.h>
#include <Adafruit_NeoPixel.h>
BS811X bs8116;
struct Pad
{
  int keymapIndex;
  int ledIndex;
};
const Pad pads[16] = {
    {14, 3}, {15, 2}, {0, 1}, {1, 0}, {10, 7}, {11, 6}, {12, 5}, {13, 4}, {6, 11}, {7, 10}, {8, 9}, {9, 8}, {2, 15}, {3, 14}, {4, 13}, {5, 12}};
#define PIN 10
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println(F("Let's freakin' go!"));
  if (!bs8116.begin(8, 9))
  {
    Serial.println("BS8116A initialization failed!");
    while (1)
      ;
  }
  pixels.begin();
  pixels.setBrightness(255);
  pixels.clear();
  pixels.show();
}
void loop()
{
  uint16_t keymap = bs8116.readKeys();
  pixels.clear();
  if (keymap > 0)
  {
    Serial.print("Key(s) pressed (bitmask): ");
    Serial.print(keymap, BIN);
    Serial.print(" -> Key(s): ");
    for (int i = 0; i < 16; i++) // i is the physical pad number
    {
      if (keymap & (1 << pads[i].keymapIndex))
      {
        pixels.setPixelColor(pads[i].ledIndex, pixels.Color(0, 255, 0));
        Serial.print(i); // Print the physical pad number
        Serial.print(" ");
      }
    }
    Serial.println();
  }
  pixels.show();
  delay(10);
}