#ifndef BS8116A_H
#define BS8116A_H

#include <Arduino.h>
#include <Wire.h>

#define BS8116A_ADDR 0x50

class BS8116A
{
public:
  BS8116A();
  bool begin(int sda, int scl);
  uint16_t readKeys();

private:
  bool init();
};

#endif
