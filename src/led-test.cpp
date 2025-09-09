#include <Adafruit_NeoPixel.h>

#define PIN 10
#define NUMPIXELS 16 // 4x4 matrix

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int ledOrder[16] = {3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12};

void setup()
{
  pixels.begin();
  pixels.setBrightness(50); // Set brightness to a moderate level
}

void loop()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.clear();                                                 // Turn off all pixels
    pixels.setPixelColor(ledOrder[i], pixels.Color(255, 255, 255)); // Turn on the current pixel (white)
    pixels.show();                                                  // Update the strip
    delay(1000);                                                    // Wait for one second
  }
}
