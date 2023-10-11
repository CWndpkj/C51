#include "SPI.h"
#include <REGX52.H>

sbit SCK  = P2 ^ 0;
sbit MOSI = P2 ^ 1;
sbit MISO = P2 ^ 2;
sbit CS   = P2 ^ 3;
/**
 * @brief MODE 可为 : 0x00,空闲为低电平,上升沿采样;0x01 空闲为为低电平,下降沿采样  ;
 * 0x02 空闲为高电平，上升沿采样 ；0x03 空闲为高电平，下降沿采样
 *
 */
#define MODE 0x00

void SPI_Init()
{
    SCK = 0;
    CS  = 1;
}

void SPI_Start()
{
    CS = 0;
}

void SPI_SendByte(unsigned char byte_data)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        MOSI = byte_data & (0x80 >> i);
        SCK  = 1;
        SCK  = 0;
    }
}

unsigned char SPI_RcvByte()
{
    unsigned char byte_data;
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SCK = 1;
        SCK = 0;
        if (MISO) {
            byte_data |= (0x80 >> i);
        }
    }
    return byte_data;
}

void SPI_Stop()
{
    CS = 1;
}

unsigned char SPI_Send_RcvByte(unsigned char byte_data)
{
    unsigned char i;
    unsigned char ret_data;
    for (i = 0; i < 8; i++) {
        MOSI = byte_data & (0x80 >> i);
        SCK  = 1;
        SCK  = 0;
        if (MISO) {
            ret_data |= (0x80 >> i);
        }
    }
    return ret_data;
}