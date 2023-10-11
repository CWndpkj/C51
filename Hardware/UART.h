#ifndef _UART_H_
#define _UART_H_
#include <REGX52.H>


void UART_Init(void(*interrupt_call_back)(unsigned char byte));	//9600bps@11.0592MHz


void UART_Send_Byte(unsigned char byte);


void UART_Recv_Routine();

#endif