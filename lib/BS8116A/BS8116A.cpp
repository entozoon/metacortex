#include "BS8116A.h"

BS8116A::BS8116A()
{
}

void BS8116A::begin(int sda, int scl)
{
  Wire.begin(sda, scl);
  Wire.setClock(100000);
}

uint16_t BS8116A::readKeys()
{
  uint8_t GET_DATA_ADDR = 0x08;
  uint8_t key_value[2] = {0, 0};

  Wire.beginTransmission(BS8116A_ADDR);
  Wire.write(GET_DATA_ADDR);
  Wire.endTransmission(false);

  Wire.requestFrom(BS8116A_ADDR, 2);

  if (Wire.available())
  {
    key_value[0] = Wire.read();
    key_value[1] = Wire.read();
  }

  return key_value[0] + (key_value[1] << 8);
}
