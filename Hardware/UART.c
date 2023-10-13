/**
 * @file UART.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  UART 通信驱动模块
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "UART.h"
#include <REGX52.H>

void(*f_ptr)(unsigned char byte);

/**
 * @brief UART 初始化
 * @param interrupt_call_back 串口接收到数据后的处理回调函数
 */
void UART_Init(void(*interrupt_call_back)(unsigned char byte))	//9600bps@11.0592MHz
{
	f_ptr=interrupt_call_back;
	//配置串口寄存器
	
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	//配置定时器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
	ES=1;//开启UART中断
	EA=1;//开启总中断
}

void UART_Send_Byte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;//软件复位
}

void UART_Recv_Routine() interrupt 4
{
	if(RI==1){//判断中断是否为接收中断
		(*f_ptr)(SBUF);
		RI=0;
	}
}