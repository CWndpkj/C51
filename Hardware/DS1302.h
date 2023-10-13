#ifndef _DS1302_H_
#define _DS1302_H_
typedef unsigned char u8;
typedef unsigned int u16;
void DS1302_Init();
void DS1302_WriteByte(u8 Addr, u8 _data);
u8 DS1302_ReadByte(u8 Addr);
void DS1302_SetTime(unsigned char *Time);
unsigned char*DS1302_GetTime();
#endif