/**
 * @file SPI.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  模拟SPI通信驱动
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SPI.h"
#include <REGX52.H>

sbit SCK  = P2 ^ 0;
sbit MOSI = P2 ^ 1;
sbit MISO = P2 ^ 2;
sbit CS   = P2 ^ 3;
/**
 * @brief MODE 可为 : 0x00,空闲为低电平,上升沿采样;0x01 空闲为为低电平,下降沿采样  ;
 *        0x02 空闲为高电平，上升沿采样 ；0x03 空闲为高电平，下降沿采样
 * @note  后三种不常见,目前只实现了第一种
 */
#define MODE 0x00


/**
 * @brief SPI 初始化
 */
void SPI_Init()
{
    SCK = 0;
    CS  = 1;
}

/**
 * @brief SPI 产生起始条件
 */
void SPI_Start()
{
    CS = 0;
}

/**
 * @brief SPI发送一个字节
 * @param byte_data  发送的字节数据
 */
void SPI_SendByte(unsigned char byte_data)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        MOSI = byte_data & (0x80 >> i);
        SCK  = 1;
        SCK  = 0;
    }
}

/**
 * @brief SPI 接收一个字节
 * @return unsigned char 接收到的字节
 */
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

/**
 * @brief SPI 发送结束信号
 */
void SPI_Stop()
{
    CS = 1;
}

/**
 * @brief SPI 发送同时接收一个字节
 * @param byte_data  要发送的字节
 * @return unsigned char  接收到的字节
 */
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