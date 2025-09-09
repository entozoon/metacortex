#include "BS8116A.h"

// Configuration data from the reference sample
static const uint8_t touch_key_init_buff[22] = {
    0x00,                         /* Trigger mode */
    0x00, 0x83, 0xF3,             /* Fixed protocol */
    0x98,                         /* Power saving mode */
    0x20, 0x20, 0x20, 0x20, 0x20, /* Touch threshold */
    0x20, 0x20, 0x20, 0x20, 0x20, /* Touch threshold */
    0x20, 0x20, 0x20, 0x20, 0x20, /* Touch threshold */
    0x40,                         /* Interrupt mode */
    0x2E                          /* SUM checksum */
};

BS8116A::BS8116A()
{
}

bool BS8116A::begin(int sda, int scl)
{
  Wire.begin(sda, scl);
  Wire.setClock(100000);
  // The chip must be initialized within 8 seconds of power-up
  return init();
}

bool BS8116A::init()
{
  uint8_t SET_ATTR_ADDR = 0xB0;
  Wire.beginTransmission(BS8116A_ADDR);
  Wire.write(SET_ATTR_ADDR);
  Wire.write(touch_key_init_buff, sizeof(touch_key_init_buff));
  return Wire.endTransmission() == 0;
}

uint16_t BS8116A::readKeys()
{
  uint8_t GET_DATA_ADDR = 0x08;
  uint8_t key_value[2] = {0, 0};

  // Point to the key data register
  Wire.beginTransmission(BS8116A_ADDR);
  Wire.write(GET_DATA_ADDR);
  if (Wire.endTransmission(false) != 0)
  {
    return 0; // Return 0 on error
  }

  // Request 2 bytes of data
  if (Wire.requestFrom(BS8116A_ADDR, 2) != 2)
  {
    return 0; // Return 0 if we didn't get 2 bytes
  }

  if (Wire.available())
  {
    key_value[0] = Wire.read(); // Low byte
    key_value[1] = Wire.read(); // High byte
  }

  // Combine the bytes, high byte first
  return (key_value[1] << 8) | key_value[0];
}
