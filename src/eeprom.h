#ifndef __eeprom_h__
#define __eeprom_h__

#include <Arduino.h>

#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13

void setAddress(int address, bool outputEnable);
byte readEEPROM(int address); 
void writeEEPROM(int address, byte data);
void printContents(int startAddress, int length);
void setupPins();
void writeDataToEeprom(int addressOffset, int dataLength, byte data[], bool wipeData, bool writeData);

#endif
