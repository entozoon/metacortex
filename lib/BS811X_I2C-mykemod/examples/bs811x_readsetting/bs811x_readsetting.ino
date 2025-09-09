// Example sketch which shows how to use Arduino to change and read settings from BS811X chip
// Connect your Arduino to BS811X and upload ino
// Open the serial port monitor
// Serial output is in format like "0,0,83,F3,D8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8"
// If you want to change settings, you may call method "setSetting" and change setting array in header
//
// created by Nitro_Ice
// snowhalation@gmail.com
//////////////////////////////////////////////////////////////////
// Connections
//
// Uno:SDA <-> A4  Mega:SDA <-> 20  Leo:SDA <-> 2
//     SCL <-> A5       SCL <-> 21      SCL <-> 3
//
//////////////////////////////////////////////////////////////////

#include <BS811X.h>

BS811X bs8116;
uint8_t data[21];

void setup()
{
    bs8116.begin("8116");             //Use "8116" or "8112" to indicate chip type
    Serial.begin(38400);
    delay(200);
}

void loop()
{
    bs8116.readSetting(data);
    for(uint8_t i = 0;i < 21;i++) {
      Serial.print(data[i], HEX);
      if(i != 20) {Serial.print(',');}
      data[i]=0;
    }
    Serial.println();
    delay(10000);
}
