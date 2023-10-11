#include <REGX52.H>
#include "MAX7219.h"
#include "SPI.h"

#define No_Open     0x00
#define Digit_0     0x01
#define Digit_1     0x02
#define Digit_2     0x03
#define Digit_3     0x04
#define Digit_4     0x05
#define Digit_5     0x06
#define Digit_6     0x07
#define Digit_7     0x08
#define DecodeMode  0x09
#define Intensity   0x0A
#define ScanLimit   0x0B
#define ShutDown    0x0C
#define DisplayTest 0x0F



void MAX7219_Init()
{
    unsigned char i;
    SPI_Init();
    SPI_Start();
    SPI_SendByte(ShutDown);
    SPI_SendByte(0x00);
    SPI_SendByte(Intensity);
    SPI_SendByte(0X05); // 设置居中亮度
    SPI_SendByte(DecodeMode);
    SPI_SendByte(0x00); // 设置译码模式
    SPI_SendByte(ScanLimit);
    SPI_SendByte(0x07); // 扫描所有位
    SPI_Stop();
    // 对寄存器进行清零
    for (i = 0; i < 8; i++) {
        MAX7219_SetData(i, 0x00);
    }
}

void MAX7219_SetBrightness(unsigned char Brightness)
{
    SPI_Start();
    SPI_SendByte(Intensity);
    SPI_SendByte(Brightness);
    SPI_Stop();
}

void MAX7219_SetData(unsigned char Digit, unsigned char Data_to_Show)
{
    SPI_Start();
    switch (Digit) {
        case 0:
            SPI_SendByte(Digit_0);
            break;
        case 1:
            SPI_SendByte(Digit_1);
            break;
        case 2:
            SPI_SendByte(Digit_2);
            break;
        case 3:
            SPI_SendByte(Digit_3);
            break;
        case 4:
            SPI_SendByte(Digit_4);
            break;
        case 5:
            SPI_SendByte(Digit_5);
            break;
        case 6:
            SPI_SendByte(Digit_6);
            break;
        case 7:
            SPI_SendByte(Digit_7);
            break;
    }
    SPI_SendByte(Data_to_Show);
    SPI_Stop();
}

void MAX7219_Show()
{
    SPI_Start();
    SPI_SendByte(ShutDown);
    SPI_SendByte(0x01);
    SPI_Stop();
}

void MAX7219_TestMode()
{
    SPI_Start();
    SPI_SendByte(DisplayTest);
    SPI_SendByte(0x01);
    SPI_Stop();
}