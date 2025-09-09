// Example sketch which shows how to use Arduino to read from BS811X touch key
// Connect your Arduino to BS811X and upload ino
// Open the serial port monitor
// Serial output is in format like "Key status:0000000000000000  Pressed key: 0"
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

void setup()
{
    bs8116.begin("8116");                      //Use "8116" or "8112" to indicate chip type
    Serial.begin(38400);
    delay(200);
}

void loop()
{
    uint16_t keymap = bs8116.readKeys();
    String map;
    for(uint8_t i = 0;i < 16;i++) {           //For 8112 should be 12 
      uint8_t bit = bitRead(keymap, i);
      if(bit) { map += '1'; }
      else { map += '0'; }
    }
    Serial.print("Key status:");
    Serial.print(map);

    uint8_t key = bs8116.getKey_active();
    Serial.print("  Pressed key: ");
    Serial.println(key);

    if(bs8116.getKey_passive(12)) {
      Serial.println("Key 12 is pressed！");
    }

    if (bs8116.getKey_edge(1, 2)) {
        Serial.println("Key 2 rising edge detected！");
    }
    else if (bs8116.getKey_edge(2, 2)) {
        Serial.println("Key 2 falling edge detected！");
    }

    delay(1000);
}
