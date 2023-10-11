#ifndef _SPI_H_
#define _SPI_H_

/**
 * @brief SPI总线初始化
 */
void SPI_Init();

/**
 * @brief SPI总线开始信号
 */
void SPI_Start();

/**
 * @brief SPI发送一个byte
 * @param byte_data 要发送的byte
 */
void SPI_SendByte(unsigned char byte_data);

/**
 * @brief SPI接收一个byte
 * @return unsigned char 接受的byte
 */
unsigned char SPI_RcvByte();

/**
 * @brief SPI停止信号
 */
void SPI_Stop();

/**
 * @brief SPI同时发送和接受byte
 * 
 * @param byte_data 要发送的byte
 * @return unsigned char 接受到的byte
 */
unsigned char SPI_Send_RcvByte(unsigned char byte_data);

#endif // !_SPI_H_
