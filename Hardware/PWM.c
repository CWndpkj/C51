/**
 * @file PWM.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  PWM生成模块,可以设置占空比,实现DA转换
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <REGX52.H>
#include "LCD1602.h"
//*************************
//更改需要进行PWM输出的端口
#define port P1_0
//**************************

unsigned int m_ratio;
unsigned char counter;


/**
 * @brief PWM初始化函数
 * @param ratio 设置占空比,分辨率1/256
 * 			    占空比=ratio/256
 */
void PWM_Init(unsigned int ratio)
{
	m_ratio=ratio;
	//对定时器进行初始化
	//1微秒@11.0592MHz
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	
	//以下设定为该单片机定时初始值最大设置限度，超过此值，定时器中断时间错误
	TL0 = 0xFD;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值

	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
	
	EA=1;						//使能总中断
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0xFD;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	
	counter++;

	port=!(counter>=m_ratio);

}