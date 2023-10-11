#include "I2C.h"
#include "delay.h"
//15开发板中AT24C02的IIC通信引脚
sbit I2C_SDA = P2^0;
sbit I2C_SCL = P2^1;
 
/**
  * @brief	I2C起始信号
  * @param	无
  * @retval	无
  */
void I2C_Start(void)
{
	I2C_SDA = 1;	//拼接其他块，确保默认是1
	I2C_SCL = 1;
	I2C_SDA = 0;	//时序上先拉低
	I2C_SCL = 0;
}
 
/**
  * @brief	I2C停止信号
  * @param	无
  * @retval	无
  */
void I2C_Stop(void)
{
	I2C_SDA = 0;	//确保默认0，保证由低电平拉高至高电平
	delayms(1);
	I2C_SCL = 1;
	delayms(1);
	I2C_SDA = 1;
	delayms(1);
}
 
/**
  * @brief	I2C发送一个字节数据
  * @param	Byte 要发送的字节
  * @retval	无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
//	I2C_SCL = 0;	//起始信号已经拉低了，无需重复
	for (i = 0; i < 8; i ++)
	{		
		I2C_SDA = Byte & (0x80>>i);	//把Byte最高位取出，赋值给I2C_SDA,依次从高到底
		I2C_SCL = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_();//需要0.4us
		I2C_SCL = 0;
	}
}
 
/**
  * @brief	I2C接收一个字节数据
  * @param	无
  * @retval	接受到的一个字节数据	
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	
	I2C_SDA = 1;	//接收之前，先把I2C_SDA置1，释放总线
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;	//拉高SCL，SCL读取SDA
		if(I2C_SDA == 1){Byte |= (0x80>>i);}
			/*如果读取到的SDA为1，把Byte最高位置1，如果读取到的SDA为0，不处理，默认最高位为0，放在循环里从高位到低位依次读取*/
		I2C_SCL = 0;	//拉低SCL，结束当前循环
	}
	return Byte;
}
 
/**
  * @brief	I2C发送应答
  * @param	AckBit 应答位，0为应答，1为非应答
  * @retval	无
  */
void I2C_SendAck(unsigned char AckBit)
{				
	I2C_SDA = AckBit;//给应答就是0，不给应答就是1
	I2C_SCL = 1;
	I2C_SCL = 0;
}
 
/**
  * @brief	I2C接收应答
  * @param	无
  * @retval	接收到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA = 1;	//先释放SDA
	I2C_SCL = 1;	//高电平期间读取SDA
	AckBit=I2C_SDA;	//读取到什么，就返回什么
	I2C_SCL = 0;
	return AckBit;	//返回0，代表有应答，返回1，代表无应答
}