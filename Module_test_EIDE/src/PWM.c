#include <REGX52.H>
#include "PWM.h"

unsigned int m_ratio;
unsigned char counter;

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