#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMPIXELS 16 // 4x4 matrix

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Helper function to generate rainbow colors
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setup()
{
  pixels.begin();
  pixels.setBrightness(50); // Set brightness to a moderate level
}

void loop()
{
  for (int j = 0; j < 256; j++)
  { // Cycle through all 256 colors in the wheel
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(20);
  }
}
