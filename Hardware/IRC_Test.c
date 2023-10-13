/**
 * @file IRC_Test.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  红外NEC协议解析函数,使用外部中断来完成对瞬间的红外脉冲的解析
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "IRC_Test.h"
#include <REGX52.H>

typedef unsigned char u8; // 基础类型定义
typedef unsigned int u16;

unsigned char Addr;    // 地址
unsigned char Command; // 命令
unsigned char Data[4]; // 储存数据

bit Data_Ready_Flag = 0;
bit Repeat_Flag = 0;
sbit INT0_input = P3 ^ 2; // 中断入口IO定义

/**
 * @brief IRC初始化,配置外部中断,配置定时器
 */
void IRC_Init()
{
    // 设置外部中断
    IT0 = 1; // 设置为下降沿触发
    EX0 = 1; // 开启外部中断1
    EA = 1;  // 开启总中断
    PX0 = 1; // 优先级设置为最高

    TMOD &= 0xF0; // 设置定时器模式
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0x00;   // 设置定时初始值
    TH0 = 0x00;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
}

/**
 * @brief IRC定时器的计数器清零,为下一次计时做准备
 */
void IRC_Timer_reset()
{
    TL0 = 0x00;
    TH0 = 0x00;
}
/**
 * @brief 获取定时器计数器值,以得出时间间隔
 * @return u16 返回计时器的计数器的值
 */
u16 IRC_Timer_Interval()
{
    return TH0 << 8 | TL0;
}
/**
 * @brief IRC 获取解析到的地址码
 * @return unsigned char 返回获取到的地址码
 */
unsigned char IRC_Get_Addr()
{
    return Addr;
}

/**
 * @brief IRC获取解析到的命令码
 * @return unsigned char 返回命令码
 */
unsigned char IRC_Get_Command()
{
    return Command;
}

/**
 * @brief IRC获取是否解析到新的数据,
 * 可以在循环中不断调用此函数,一旦用新的数据,便可对数据进行获取
 * @note 若data_ready未被置位,直接读取数据会得到上一次的数据
 * @return bit 返回是否有新的数据,0代表没有,1代表有,读取后自动清零
 */
bit Get_Data_Ready_Flag()
{
    if (Data_Ready_Flag)
    {
        Data_Ready_Flag = 0;
        return 1;
    }
    else
        return 0;
}
/**
 * @brief 获取是否得到了NEC重发指令
 * @return bit 返回是否存在repeat指令,0代表没有,1代表有,读取后自动清零
 */
bit Get_Repeat_Flag()
{
    if (Repeat_Flag)
    {
        Repeat_Flag = 0;
        return 1;
    }
    else
        return 0;
}

/**
 * @brief 外部中断函数,在此处理每次发来的数据
 * 		  每次在此函数处理全过程的NEC协议,
 * 		  缺点是在等待中耗费大量的CPU时间
 * 		  优点是相较于状态机机制的解析,
 * 		  更灵活,相对稳定
 */
void IRC_INT0_Routine() interrupt 0
{
    u16 interval;
    u8 i;
    u8 j;

    // 关闭外部中断1，防止二次调用函数
    EX0 = 0;
    // 9ms的低电平才确定为信号的开始信号
    IRC_Timer_reset();
    while (INT0_input == 0)
        ; // 等待前面9ms的低电平过去
    interval = IRC_Timer_Interval();
    if (interval > 8000) // 若低电平持续的时间小于8ms证明为有效信号
    {
        IRC_Timer_reset();
        while (INT0_input == 1)
            ; // 高电平时间
        interval = IRC_Timer_Interval();
        if (interval > 3000)
        {
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    while (INT0_input == 0)
                        ; // 前560us低电平
                    IRC_Timer_reset();
                    while (INT0_input == 1)
                        ; // 高电平时间监测
                    interval = IRC_Timer_Interval();
                    Data[i] >>= 1;        // i表示第几组数据
                    if (interval >= 1000) // 如果高电平出现大于1000us，那么是1
                    {
                        Data[i] |= 0x80;
                    }
                }
            }
            while (INT0_input == 0)
                ; // 注意此处需要等待32bit数据发送完后多出来的低电平
            if (Data[0] == ~Data[1] && Data[2] == ~Data[3])
            {
                Addr = Data[0];
                Command = Data[2];
                Data_Ready_Flag = 1;
            }
        }
        else // Repeat信号
        {
            Repeat_Flag = 1;
            while (INT0_input == 0)
                ; // 此处repeat同样需要等待发送完后多出的低电平
        }
    }
    IE0 = 0; // 此时外部中断1的中断标志位为1，若不手动清零，开启外部中断1后将立马再次进入中断
    EX0 = 1;
}
