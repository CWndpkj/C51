#include <REGX52.H>
#include "24C02.h"
#include "IIC.h"
#include "LCD1602.h"
#include "delay.h"

void _24C02_WriteByte(unsigned char byte_data, unsigned char addr)
{
    IIC_Start();
    IIC_SendByte(0xA0);
    IIC_RcvAck();
    IIC_SendByte(addr);
    IIC_RcvAck();
    IIC_SendByte(byte_data);
    IIC_RcvAck();
    IIC_Stop();
    delayms(6);
}

unsigned char _24C02_ReadByte(unsigned char addr)
{
    unsigned char buff = 0x00;
    IIC_Start();
    IIC_SendByte(0xA0);
    IIC_RcvAck();
    IIC_SendByte(addr);
    IIC_RcvAck();
    IIC_Start();
    IIC_SendByte(0xA1);
    IIC_RcvAck();
    buff = IIC_ReadByte();
    IIC_SendAck(1);
    IIC_Stop();
    return buff;
}