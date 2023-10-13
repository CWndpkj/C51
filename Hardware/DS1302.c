/**
 * @file DS1302.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  DS1302驱动函数
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "DS1302.h"
#include "delay.h"
#include <REGX52.H>

#define DS1302_Second 0x80
#define DS1302_Minute 0x82
#define DS1302_Hour 0x84
#define DS1302_Date 0x86
#define DS1302_Month 0x88
#define DS1302_Day 0x8A
#define DS1302_Year 0x8C
#define DS1302_WP 0x8E
// TODO:更改为适当地引脚
sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_CE = P3 ^ 5;

/**
 * @brief DS1302时间数据数组,顺序为 年月日,时分秒,星期
 *///                 年   月  日  时 分 秒 星期
u8 DS1302_Time[7] = {2004, 11, 24, 0, 0, 0, 6};

/**
 * @brief DS1302初始化
 */
void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    DS1302_IO = 0;
}

/**
 * @brief DS1302写一个字节
 *
 * @param Addr 写入的地址
 * @param _data 写入的数据
 */
void DS1302_WriteByte(u8 Addr, u8 _data)
{
    u8 i;
    DS1302_Init();
    DS1302_CE = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Addr & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = _data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}

/**
 * @brief DS1302读取一个字节
 *
 * @param Addr 读取地址
 * @return u8  读取到的数据
 */
u8 DS1302_ReadByte(u8 Addr)
{
    u8 i;
    u8 _data = 0x00;
    DS1302_Init();
    DS1302_CE = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 0;
        DS1302_IO = Addr & (0x01 << i);
        DS1302_SCLK = 1;
    }
    DS1302_SCLK = 0;
    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 0;
        if (DS1302_IO)
        {
            _data |= (0x01 << i);
        }
        DS1302_SCLK = 1;
    }
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    return _data;
}

/**
 * @brief BCD码转10进制
 * @param BCD_Data 传入BCD数据
 * @return u8 返回10进制的数据
 */
u8 DS1302_BCD2Decimal(u8 BCD_Data)
{
    return BCD_Data / 16 * 10 + BCD_Data % 16;
}
/**
 * @brief 十进制转BCD码
 * @param Decimal_Data 传入十进制的数据
 * @return u8           返回BCD数据
 */
u8 DS1302_Decimal2BCD(u8 Decimal_Data)
{
    return Decimal_Data / 10 * 16 + Decimal_Data % 10;
}

void DS1302_SetTime(unsigned char *Time)
{
    // 关闭写保护
    DS1302_WriteByte(DS1302_WP, 0x00);
    // 将初始的时间数据设置到DS1302中
    DS1302_WriteByte(DS1302_Year, DS1302_Decimal2BCD(Time[0]));
    DS1302_WriteByte(DS1302_Month, DS1302_Decimal2BCD(Time[1]));
    DS1302_WriteByte(DS1302_Date, DS1302_Decimal2BCD(Time[2]));
    DS1302_WriteByte(DS1302_Hour, DS1302_Decimal2BCD(Time[3]));
    DS1302_WriteByte(DS1302_Minute, DS1302_Decimal2BCD(Time[4]));
    DS1302_WriteByte(DS1302_Second, DS1302_Decimal2BCD(Time[5]));
    DS1302_WriteByte(DS1302_Day, DS1302_Decimal2BCD(Time[6]));
    // 开启写保护
    DS1302_WriteByte(DS1302_WP, 0x80);
}
/**
 * @brief DS1302获取当前时间
 * @return unsigned char* 返回一个含有时间信息的数组指针,其中包含的日期数据信息定义在文件头
 */
unsigned char *DS1302_GetTime()
{
    DS1302_Time[0] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Year | 0x01));
    DS1302_Time[1] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Month | 0x01));
    DS1302_Time[2] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Date | 0x01));
    DS1302_Time[3] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Hour | 0x01));
    DS1302_Time[4] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Minute | 0x01));
    DS1302_Time[5] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Second | 0x01));
    DS1302_Time[6] = DS1302_BCD2Decimal(DS1302_ReadByte(DS1302_Day | 0x01));
    return DS1302_Time;
}
