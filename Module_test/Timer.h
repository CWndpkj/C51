#ifndef _TIMER_H_
#define _TIMER_H_
#include <REGX52.H>
/*
定时器与中断模块
*/
/*
定时器初始化函数
@param  unsigned char timer_id        定时器ID(范围1,2)
@param  unsigned int interval         定时的时间间隔
@param  unsigned char prefer          中断的优先级(范围 0-3)
@param  void(*interrupt_callback)()		中断的回调函数
*/
void TimerInit(unsigned char timer_id,unsigned int interval,unsigned char prefer,void(*interrupt_callback)());

//定时器的中断函数
void Timer0_Routine();


void Timer1_Routine();
#endif