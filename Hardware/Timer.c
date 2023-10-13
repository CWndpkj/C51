/**
 * @file Timer.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  定时器设置函数
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Timer.h"

// 中断回调函数,在定时器溢出时将调用该函数
void (*f_ptr)();

// 定时间隔
static unsigned int _1ms = 0;
static unsigned int m_interval = 0;


/**
 * @brief 定时器初始化函数
 * 
 * @param timer_id 定时器ID(范围1,2)
 * @param interval 定时的时间间隔
 * @param prefer 中断的优先级(范围 0-3)
 * @param interrupt_callback 中断的回调函数
 */
void TimerInit(unsigned char timer_id, unsigned int interval, unsigned char prefer, void (*interrupt_callback)())
{
    f_ptr = interrupt_callback;
    m_interval = interval;
    EA = 1; // 开启中断的总开关

    // 100微秒@11.0592MHz
    if (timer_id == 0)
    {
        TMOD &= 0xF0; // 设置定时器模式
        TMOD |= 0x01; // 设置定时器模式
        TL0 = 0xA4;   // 设置定时初始值
        TH0 = 0xFF;   // 设置定时初始值
        TF0 = 0;      // 清除TF0标志
        TR0 = 1;      // 定时器0开始计时
        ET0 = 1;      // 使能定时器0中断
        // 设置优先级
        PT0 = prefer;
    }
    else if (timer_id == 1)
    {
        TMOD &= 0x0F; // 设置定时器模式
        TMOD |= 0x10; // 设置定时器模式
        TL1 = 0xA4;   // 设置定时初始值
        TH1 = 0xFF;   // 设置定时初始值
        TF1 = 0;      // 清除TF0标志
        TR1 = 1;      // 定时器0开始计时
        ET1 = 1;      // 使能定时器0中断

        // 设置优先级
        PT1 = prefer;
    }
}
// 定时器的中断函数
void Timer0_Routine() interrupt 1
{
    TL0 = 0x66; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    _1ms++;
    if (_1ms >= m_interval)
    {
        // TODO:添加需要终端执行的代码
        (*f_ptr)();
        _1ms = 0;
    }
}

void Timer1_Routine() interrupt 3
{
    TL1 = 0xA4; // 设置定时初始值
    TH1 = 0xFF; // 设置定时初始值
    _1ms++;
    if (_1ms >= m_interval)
    {
        // TODO:添加需要终端执行的代码
        (*f_ptr)();
        _1ms = 0;
    }
}