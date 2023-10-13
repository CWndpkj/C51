/**
 * @file AT24C02.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief AT24C02读取,写入函数,需要配合模拟IIC驱动使用
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <REGX52.H>
#include "AT24C02.h"
#include "IIC.h"
#include "LCD1602.h"
#include "delay.h"


/**
 * @brief 使用模拟I2C(IIC)读取AT24C02
 * 
 * @param byte_data 需要写入的数据
 * @param addr      数据写入的地址
 */
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
    //AT24C02写入后有一段时间状态为忙,不响应任何请求    
    //此处适当延时,防止在连续读取过快时出现问题
    delayms(6);
}


/**
 * @brief 使用模拟I2C(IIC)读取AT24C02
 * 
 * @param addr 需要读取的地址
 * @return unsigned 返回读取到的数据
 */
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
    IIC_SendAck(1);//发送非应答
    IIC_Stop();
    return buff;
}