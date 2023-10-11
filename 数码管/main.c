#include <REGX52.H>
#include "LCD1602.h"
#include "8bit_SMG.h"
#include "delay.h"
#include "matrixkey.h"
typedef unsigned int u16;	//对数据类型进行自定义
typedef unsigned char u8;

//void main()
//{			 
////	u16	i=2000;
//	unsigned char ret=0;
//	//LCD_Init();
//	while(1)
//	{
////   	while(i--)//??2000?
////	{
////		LED=!LED;
////		BEEP=!BEEP;//???????????
////		delay(1);
////	}
////	i=0;//??
////	BEEP=0;//?????
////	LED=1;
////		while(1)
////		{
////			SMG_display(0,0);
////			SMG_display(1,1);
////			SMG_display(2,2);
////			SMG_display(3,3);
////			SMG_display(4,4);
////			
////		}
//		  //LCD_ShowString(1,1,"helloworld");
//		
//				ret=GetKey();
//				if(ret!=100){
//					SMG_display(1,ret/10);
//					SMG_display(2,ret%10);
//				}
//				else 
//					SMG_display(0,'F');
//	}	
//	
//	
//	
//}




#include <stdio.h>
void main(void)
{
SCON = 0x50; //串口方式 1,允许接收
TMOD = 0x20; //定时器 1 定时方式 2
TCON = 0x40; //设定时器 1 开始计数
TH1 = 0xE8; //11.0592MHz 1200 波特率
TL1 = 0xE8;
TI = 1;
TR1 = 1; //启动定时器
while(1)
{
printf ("Hello World!\n"); //显示 Hello World
}
}