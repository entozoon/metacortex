#include <Arduino.h>
#include <Wire.h>
#include <BS811X.h>
#include <Adafruit_NeoPixel.h>
BS811X bs8116;
const int keyOrder[16] = {14, 15, 0, 1, 10, 11, 12, 13, 6, 7, 8, 9, 2, 3, 4, 5};
#define PIN 10
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int ledOrder[16] = {3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12};
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
      int keymapIndex = keyOrder[i]; // The bit in the keymap corresponding to this pad
      if (keymap & (1 << keymapIndex))
      {
        int ledIndex = ledOrder[i]; // The LED corresponding to this pad
        pixels.setPixelColor(ledIndex, pixels.Color(255, 255, 255));
        Serial.print(i); // Print the physical pad number
        Serial.print(" ");
      }
    }
    Serial.println();
  }
  pixels.show();
  delay(100);
}
