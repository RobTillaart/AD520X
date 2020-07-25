# AD520X

Arduino library for SPI AD5204 and AD5206 digital potentiometers

## Description

The **AD5204** and **AD5206** are SPI based digital potentiometers.
The **AD5204** has 4 ports and the **AD5206** has 6 ports.

The interface is quite straightforward, check the example(s).

_Although not tested this library should work for the older **AD8400** (single port),
the **AD8402** (dual port) and **AD8403** (quad port) as the interface is very similar
(datasheet comparison). If you can confirm it works, please let me know._

## Interface

- **AD520X(reset = 255)** constructor using hardware SPI,  
default = no reset pin = 255
- **AD520X(data, clock, select, reset = 255)** constructor using software SPI  
default = no reset pin = 255
- **begin(ports = 6, value = 128)** ports = { 6, 4, 2, 1 } 
value is the initial value of all potmeters.
- **setValue(idx, value)** set a potmeter to a value
- **setAll(value)** set all potmeters to same value e.g. 0 or max or mid
- **getValue(idx)** returns the last set value.
- **reset(value = 128)** resets all pins to the value postion, default 128.

Constructors are also available for 
- **AD5204()** and **AD5206()**
- **AD8400()** **AD8402()** and **AD8403()**.

These classes are 100% identical, no specifics for now.

## Future

- powerOn() powerOff() - shutdown pin
- invert flag per potmeter? 0..255 -> 255..0  
- logarithmic effect? gamma function?

- follow(pinB, pinA, percentage = 100)  
makes pinB follow pin A unless pinB is addressed explicitly  
array cascade = 0xFF or pinA.  
It will follow pinA for certain percentage default 100.

## Operations

See examples.
