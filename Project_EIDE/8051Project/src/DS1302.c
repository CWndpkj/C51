#include "DS1302.h"
#include <REGX52.H>
#include "delay.h"
#define DS1302_Second 0x80
#define DS1302_Minute 0x82
#define DS1302_Hour   0x84
#define DS1302_Date   0x86
#define DS1302_Month  0x88
#define DS1302_Day    0x8A
#define DS1302_Year   0x8C
#define DS1302_WP     0x8E
sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO   = P3 ^ 4;
sbit DS1302_CE   = P3 ^ 5;

/**
 * @brief DS1302时间结构体，顺序为：年，月，日，时，分，秒，星期
 */
u8 DS1302_Time[7] = {2004, 11, 24, 0, 0, 0, 6};

void DS1302_Init()
{
    DS1302_CE   = 0;
    DS1302_SCLK = 0;
    DS1302_IO   = 0;
}

void DS1302_WriteByte(u8 command, u8 _data)
{
    u8 i;
    DS1302_Init();
    DS1302_CE = 1;
    for (i = 0; i < 8; i++) {
        DS1302_IO   = command & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    for (i = 0; i < 8; i++) {
        DS1302_IO   = _data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}

u8 DS1302_ReadByte(u8 command)
{
    u8 i;
    u8 _data = 0x00;
    DS1302_Init();
    DS1302_CE = 1;
    for (i = 0; i < 8; i++) {
        DS1302_SCLK = 0;
        DS1302_IO   = command & (0x01 << i);
        DS1302_SCLK = 1;
    }
    DS1302_SCLK = 0;
    for (i = 0; i < 8; i++) {
        DS1302_SCLK = 0;
        if (DS1302_IO) {
            _data |= (0x01 << i);
        }
        DS1302_SCLK = 1;
    }
    DS1302_CE = 0;
    DS1302_SCLK=0;
    return _data;
}
u8 DS1302_BCD2Decimal(u8 BCD_Data)
{
    return BCD_Data / 16 * 10 + BCD_Data % 16;
}

u8 DS1302_Decimal2BCD(u8 Decimal_Data)
{
    return Decimal_Data / 10 * 16 + Decimal_Data % 10;
}

void DS1302_SetTime(unsigned char *Time)
{
    // 关闭写保护
    DS1302_WriteByte(DS1302_WP, 0x00);
    // 写入时间数据
    DS1302_WriteByte(DS1302_Year, DS1302_Decimal2BCD(Time[0]));
    DS1302_WriteByte(DS1302_Month, DS1302_Decimal2BCD(Time[1]));
    DS1302_WriteByte(DS1302_Date, DS1302_Decimal2BCD(Time[2]));
    DS1302_WriteByte(DS1302_Hour, DS1302_Decimal2BCD(Time[3]));
    DS1302_WriteByte(DS1302_Minute, DS1302_Decimal2BCD(Time[4]));
    DS1302_WriteByte(DS1302_Second,DS1302_Decimal2BCD(Time[5]));
    DS1302_WriteByte(DS1302_Day, DS1302_Decimal2BCD(Time[6]));
    // 开启写保护
    DS1302_WriteByte(DS1302_WP, 0x80);
}

unsigned char*DS1302_GetTime()
{
    DS1302_Time[0]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Year|0x01));
    DS1302_Time[1]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Month|0x01));
    DS1302_Time[2]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Date|0x01));
    DS1302_Time[3]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Hour|0x01));
    DS1302_Time[4]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Minute|0x01));
    DS1302_Time[5]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Second|0x01));
    DS1302_Time[6]=DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Day|0x01));
    return DS1302_Time;
}
