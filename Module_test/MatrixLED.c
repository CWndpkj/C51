#include "MatrixLED.h"
#include "74HC595.h"
#include <REGX52.H>
#include "delay.h"
#define MATRIXLED_PORT P0 //矩阵LED的共阴极

void MatrixLED_ShowColumn(unsigned char column,unsigned char byte)
{
	MATRIXLED_PORT=~(0x80>>column);
	_74HC595_WriteByte(byte);
	//消除残影
	_74HC595_WriteByte(0x00);
}