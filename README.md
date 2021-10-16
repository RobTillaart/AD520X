
[![Arduino CI](https://github.com/RobTillaart/AD520X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD520X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD520X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD520X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD520X/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD520X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD520X.svg?maxAge=3600)](https://github.com/RobTillaart/AD520X/releases)


# AD520X

Arduino library for SPI AD5204 and AD5206 digital potentiometers

Should work for the AD840x series too (not tested). 


## Description

The library is still experimental as not all functionality is tested (enough).

The **AD5204** (4 pm) and **AD5206** (6 pm) are SPI based digital potentiometers.
This library consists of a base class **AD520X** that does the work.

The interface is straightforward, one can set a value per pm between 0..255.

| type   | # channels |
|:-------|:----------:|
| AD5204 |  4         |
| AD5206 |  6         |
| AD8400 |  1         |
| AD8402 |  2         |
| AD8403 |  4         |


_Although not tested this library should work for the older **AD8400** (1 pm),
the **AD8402** (2 pm) and **AD8403** (4 pm) as the interface is very similar
(datasheet comparison). If you can confirm it works, please let me know._


## Interface


### Constructors

All pins are type uint8_t 

- **AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut = 255, uint8_t clock = 255)** constructor  
Base class, not to be used directly.
If dataOut and clock are set to 255 (default) it uses hardware SPI. 
If dataOut and clock are set to another (valid) value) it uses software SPI.
reset and shutdown may be set to 255 too, which effectively disables them.  
- **AD5204(select, reset, shutdown, dataOut = 255, clock = 255)** uses 4 pm.
- **AD5206(select, reset, shutdown, dataOut = 255, clock = 255)** uses 6 pm.
- **AD8400(select, reset, shutdown, dataOut = 255, clock = 255)** uses 1 pm.
- **AD8402(select, reset, shutdown, dataOut = 255, clock = 255)** uses 2 pm.
- **AD8403(select, reset, shutdown, dataOut = 255, clock = 255)** uses 4 pm.

Note: hardware SPI is 10+ times faster on an UNO.


### Base

Since 0.2.0 the functions have more default parameters.

- **void begin(uint8_t value = 128)** value is the initial value of all potentiometer.
- **void setValue(uint8_t pm = 0, uint8_t value = 128)** set a potentiometer to a value. Defaults
- **void setAll(uint8_t value)** set all potentiometers to the same value e.g. 0 or max or mid value.
- **uint8_t getValue(uint8_t pm = 0)** returns the last set value of a specific potentiometer.
- **void reset(uint8_t value = 128)** resets all potentiometers to value, default 128.
- **void setPercentage(uint8_t pm = 0, float percentage = 50)** same as setValue, now from 0..100%
- **float getPercentage(uint8_t pm = 0)** return value as percentage.


### Hardware SPI

To be used only if one needs a specific speed for hardware SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.


### ESP32 specific

This functionality is new in 0.1.2 and it is expected that the interface will change
in the future. 

- **void selectHSPI()** in case hardware SPI, the ESP32 has two options HSPI and VSPI.
- **void selectVSPI()** see above.
- **bool usesHSPI()** returns true if HSPI is used.
- **bool usesVSPI()** returns true if VSPI is used.

The **selectVSPI()** or the **selectHSPI()** needs to be called 
BEFORE the **begin()** function.


### Misc

- **uint8_t pmCount()** returns the number of internal potentiometers.
- **void powerOn()** switches the module on.
- **void powerOff()** switches the module off.
- **void powerDown()** OBSOLETE => use powerOff() instead.
- **bool isPowerOn()** returns true if on (default) or false if off.


## Future


### should

Easier than re-soldering.

- **void setInvert(uint8_t pm)** invert flag per potentiometer
   - 0..255 -> 255..0
   - 1 uint8_t can hold 8 flags
- **bool getInvert(uint8_t pm)**


### could

- **void follow(pm_B, pm_A, float percentage = 100)**
  - makes pm_B follow pm_A unless pm_B is addressed explicitly
  - e.g. to be used for stereo channels.
  - array cascade = 0xFF or pm_A.
  - It will follow pm_A for certain percentage default 100.
- **void setGamma(uint8_t pm, float gamma)**
  - logarithmic effect? easier with setPercentage()
  - see gamma library.


## Operations

See examples.
