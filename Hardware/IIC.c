/**
 * @file IIC.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief 模拟IIC
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <REGX52.H>
#include "IIC.h"
#include "LCD1602.h"
#include "delay.h"

//TODO:修改SDL与SCK的IO
sbit SDA = P2 ^ 0;
sbit SCK = P2 ^ 1;

/**
 * @brief 延时函数
 */
void Delay10us()
{
    unsigned char a, b;
    for (b = 1; b > 0; b--)
        for (a = 2; a > 0; a--)
            ;
}

/**
 * @brief IIC 产生起始信号
 */
void IIC_Start()
{
    SDA = 1;
    SCK = 1;
    SDA = 0;
    SCK = 0;
}

/**
 * @brief IIC产生结束信号
 */
void IIC_Stop()
{
    SDA = 0;
    SCK = 1;
    SDA = 1;
}

/**
 * @brief IIC发送一个bit
 * @param bit_data 发送的bit 取0或1
 */
void IIC_SendBit(bit bit_data)
{
    SDA = bit_data;
    SCK = 1;
    SCK = 0;
}

/**
 * @brief IIC发送一个Byte
 * @param byte_data 要发送的Byte
 */
void IIC_SendByte(unsigned char byte_data)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        IIC_SendBit(byte_data & (0x80 >> i));
    }
    SDA = 1; // 释放SDA
}
/**
 * @brief IIC发送是否应答
 * @param value 是否发送应答 ,0为应答,1 为非应答
 */
void IIC_SendAck(bit value)
{
    IIC_SendBit(value);
}
/**
 * @brief IIC接受应答
 * @return bit 返回是否接收到应答,
 *         在不需要验证是否接收到应答时可以选择不接受返回值
 */
bit IIC_RcvAck()
{
    return IIC_ReadBit();
}

/**
 * @brief IIC读取一个bit
 * @return bit 读取到的一个bit
 */
bit IIC_ReadBit()
{
    bit bit_data;
    SCK = 1;
    bit_data = SDA;
    SCK      = 0;
    return bit_data;
}
/**
 * @brief IIC读取一个Byte
 * @return unsigned char 读取到的Byte
 */
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