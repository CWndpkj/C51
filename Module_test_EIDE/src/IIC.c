#include <REGX52.H>
#include "IIC.h"
#include "LCD1602.h"
#include "delay.h"
/**
 * @brief TODO:修改SDL与SCK的IO
 *
 */
sbit SDA = P2 ^ 0;
sbit SCK = P2 ^ 1;

void Delay10us()
{
    unsigned char a, b;
    for (b = 1; b > 0; b--)
        for (a = 2; a > 0; a--)
            ;
}

void IIC_Start()
{
    SDA = 1;
    SCK = 1;
    SDA = 0;
    SCK = 0;
}
void IIC_Stop()
{
    SDA = 0;
    SCK = 1;
    SDA = 1;
}

void IIC_SendBit(bit bit_data)
{
    SDA = bit_data;
    SCK = 1;
    SCK = 0;
}

void IIC_SendByte(unsigned char byte_data)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        IIC_SendBit(byte_data & (0x80 >> i));
    }
    SDA = 1; // 释放SDA
}

void IIC_SendAck(bit value)
{
    IIC_SendBit(value);
}

bit IIC_RcvAck()
{
    return IIC_ReadBit();
}

bit IIC_ReadBit()
{
    bit bit_data;
    SCK = 1;
    bit_data = SDA;
    SCK      = 0;
    return bit_data;
}

unsigned char IIC_ReadByte()
{
    unsigned char byte_data = 0x00;
    unsigned char i;
    for (i = 0; i < 8; i++) {
        if (IIC_ReadBit()) {
            byte_data |= (0x80 >> i);
        }
    }
    return byte_data;
}