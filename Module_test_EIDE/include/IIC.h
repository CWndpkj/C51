#ifndef _IIC_H_
#define _IIC_H_

/**
 * @brief IIC总线开始信号
 */
void IIC_Start();

/**
 * @brief IIC总线结束信号
 */
void IIC_Stop();

/**
 * @brief IIC发送一个bit的数据
 * @param bit_data 要发送的bit
 */
void IIC_SendBit(bit bit_data);

/**
 * @brief IIC发送给一个Byte的数据
 * @param byte_data 要发送的byte
 */
void IIC_SendByte(unsigned char byte_data);

/**
 * @brief IIC主机是否发送应答
 * @param value 0为应答，1为非应答
 */
void IIC_SendAck(bit value);

/**
 * @brief IIC主机接收应答
 * @return bit 是否接收到应答，0为应答，1为非应答
 */
bit IIC_RcvAck();

/**
 * @brief IIC接收一个bit
 * @return bit 接收的字节
 */
bit IIC_ReadBit();

/**
 * @brief IIC接收一个Byte
 * @return unsigned char 接收的byte
 */
unsigned char IIC_ReadByte();
#endif // !_IIC_H_