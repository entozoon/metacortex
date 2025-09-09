#include <Arduino.h>
#include <Wire.h>
#include <BS8116A.h>

BS8116A bs8116a;

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("BS8116A Keypad Test");
  if (!bs8116a.begin(8, 9))
  {
    Serial.println("BS8116A initialization failed!");
    while (1)
      ;
  }
}

void loop()
{
  uint16_t keymap = bs8116a.readKeys();

  if (keymap > 0)
  {
    Serial.print("Key(s) pressed: ");
    for (int i = 0; i < 30; i++)
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
