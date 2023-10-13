/**
 * @file MatrixLED.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  使用74HC595控制的矩阵LED的驱动函数
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "MatrixLED.h"
#include "74HC595.h"
#include <REGX52.H>
#include "delay.h"
#define MATRIXLED_PORT P0 //矩阵LED的共阴极

/**
 * @brief 每次显示一个列,可以在循环中利用扫描显示多个列
 * @param column 选中某一列 范围:0~7
 * @param byte 	 设置该列显示的数据,8bit 范围0x00~0xFF
 */
void MatrixLED_ShowColumn(unsigned char column,unsigned char byte)
{
	MATRIXLED_PORT=~(0x80>>column);
	_74HC595_WriteByte(byte);
	//消除残影
	_74HC595_WriteByte(0x00);
}