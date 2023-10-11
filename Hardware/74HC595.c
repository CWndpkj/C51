#include "74HC595.h"
#include <REGX52.H>

//定义IO口
sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;


void _74HC595_Init()
{
	RCK=0;
	SCK=0;
}
void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		SER=byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}