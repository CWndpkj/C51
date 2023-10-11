#ifndef __AT24C02_H__
#define __AT24C02_H__
 
#include <REGX52.H>
#include "I2C.h"
 
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);
 
#endif