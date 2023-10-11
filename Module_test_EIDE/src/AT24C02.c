#include "AT24C02.h"
#include "delay.h"
#define AT24C02_ADDRESS 0xA0 // 从机地址+写  1010 0000

/**
 *@brief   名称：AT24C02写入一个字节
 *@param   参数：WordAddess 要写入字节的地址(0~255)
 *@param   参数: Data 要写入的数据
 *@retval返回值：无
 */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS); // 从机地址+写
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress); // 要写入数据的地址
    I2C_ReceiveAck();
    I2C_SendByte(Data); // 写入数据
    I2C_ReceiveAck(); // 接受应答
    I2C_Stop();
	delayms(6);//进入写周期，对任何输入无响应
}

/**
 *@brief   名称：AT24C02读取一个字节
 *@param   参数：WordAddess 要读出字节的地址
 *@retval返回值：读出的数据
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddess)
{
    unsigned char Ack;
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS); // 从机地址+写
    I2C_ReceiveAck();
    I2C_SendByte(WordAddess); // 数据的地址
    Ack = I2C_ReceiveAck();
    if (Ack == 0) {
        P2_7 = 0;
    }
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS | 0x01); // 发送从机地址+读本函数第二个函数,或上0x01变成读地址(0xA1)
    I2C_ReceiveAck();
    Data = I2C_ReceiveByte();
    I2C_SendAck(1); // 不发送应答
    I2C_Stop();

    return Data;
}