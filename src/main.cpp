#include <Arduino.h>
#include <Wire.h>
#include <BS811X.h>

BS811X bs8116;

void setup()
{
  Serial.begin(115200);
  delay(3000);
  if (!bs8116.begin("8116", 8, 9))
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
        Serial.print(i + 1);
        Serial.print(" ");
      }
    }
    Serial.println();
  }

  delay(100);
}
