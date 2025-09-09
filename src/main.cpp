#include <Arduino.h>
#include <Wire.h>
#include <BS811X.h>

BS811X bs8116;

const int keyOrder[16] = {15, 16, 1, 2, 11, 12, 13, 14, 7, 8, 9, 10, 3, 4, 5, 6};

void setup()
{
  Serial.begin(115200);
  delay(3000);
  if (!bs8116.begin(8, 9))
  {
    Serial.println("BS8116A initialization failed!");
    while (1)
      ;
  }
}

void loop()
{
  uint16_t keymap = bs8116.readKeys();

  if (keymap > 0)
  {
    Serial.print("Key(s) pressed: ");
    for (int i = 0; i < 16; i++)
    {
      if (keymap & (1 << i))
      {
        Serial.print(keyOrder[i]);
        Serial.print(" ");
      }
    }
    Serial.println();
  }

  delay(100);
}
