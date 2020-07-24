//
//    FILE: AD520X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.0.1
// PURPOSE: Arduino library for AD5204 and AD5206 igital potentiometers
//     URL: https://github.com/RobTillaart/AD520X
//
// HISTORY:
// 0.0.1    2020-07-24 initial version
// 

#include "AD520X.h"

AD520X::AD520X(uint8_t reset)
{
  _hwSPI = true;
  _reset = reset;
}

AD520X::AD520X(uint8_t data, uint8_t clock, uint8_t select, uint8_t reset)
{
  _hwSPI = false;
  _data = data;
  _clock = clock;
  _select = select;
  _reset = reset;
}

// initializes the SPI
void AD520X::begin(uint8_t ports, uint8_t value)
{
  _ports = 6;
  if (ports == 4) _ports = 4;
  if(_hwSPI)
  {
    SPI.begin();
    delay(1);
  }
  else
  {
    pinMode(_data, OUTPUT);
    pinMode(_clock, OUTPUT);
    pinMode(_select, OUTPUT);
    digitalWrite(_select, HIGH);
    digitalWrite(_data, LOW);
    digitalWrite(_clock, LOW);
  }
  if (_reset != 255)
  {
    pinMode(_reset, OUTPUT);
    digitalWrite(_reset, LOW);
  }
  setAll(value);
}

void AD520X::setValue(uint8_t idx, uint8_t value)
{
  if (idx >= _ports) return;
  _value[idx] = value;
  updateDevice(idx);
}

void  AD520X::setAll(uint8_t value)
{
  for (uint8_t p = 0; p < _ports; p++)
  {
    setValue(p, value);
  }
}

uint8_t AD520X::getValue(uint8_t idx)
{
  if (idx >= _ports) return 0;
  return _value[idx];
}

void AD520X::reset(uint8_t value)
{
  if (_reset != 255)
  {
    digitalWrite(_reset, HIGH);
    digitalWrite(_reset, LOW);
  }
  setAll(value);
}

void AD520X::updateDevice(uint8_t idx)
{
  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_select, LOW);
    SPI.transfer(idx);
    SPI.transfer(_value[idx]);
    digitalWrite(_select, HIGH);
    SPI.endTransaction();
  }
  else // Software SPI
  {
    digitalWrite(_select, LOW);
    swSPI_transfer(idx);
    swSPI_transfer(_value[idx]);
    digitalWrite(_select, HIGH);
  }
}

// simple one mode version
void AD520X::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_data,(value & mask) != 0);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
  }
}

// -- END OF FILE --

