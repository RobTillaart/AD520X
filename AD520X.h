#pragma once
//
//    FILE: AD520X.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.0.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers
//     URL: https://github.com/RobTillaart/AD520X
//
// HISTORY:
// see AD520X.cpp file
//

#include "Arduino.h"
#include "SPI.h"

#define AD520X_LIB_VERSION   "0.0.1"

class AD520X
{
public:
  AD520X(uint8_t reset = 255);
  AD520X(uint8_t data, uint8_t clock, uint8_t select, uint8_t reset = 255);  

  void     begin(uint8_t ports = 6, uint8_t value = 128);

  void     setValue(uint8_t idx, uint8_t value);
  void     setAll(uint8_t value);
  uint8_t  getValue(uint8_t idx);
  void     reset(uint8_t value = 128);

private:
  uint8_t _data;
  uint8_t _clock;
  uint8_t _select;
  uint8_t _reset;
  bool    _hwSPI;
  uint8_t _ports = 6;
  uint8_t _value[6];

  void    updateDevice(uint8_t idx);
  void    swSPI_transfer(uint8_t value);
};

class AD5204 : public AD520X
{
};

class AD5206 : public AD520X
{
};

// -- END OF FILE -- 
