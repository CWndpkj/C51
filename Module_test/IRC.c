#include <REGX52.H>
#include "IRC.h"
#include <intrins.h>
typedef unsigned char u8;//基础类型定义
typedef unsigned int u16;

unsigned char Addr;//地址
unsigned char Command;//命令

unsigned char Data[4];//储存数据
unsigned char pData=0;//数据指针

bit Data_Ready_Flag=0;
bit Repeat_Flag=0;
sbit INT0_input=P3^2;//中断入口IO定义

void IRC_Init()
{
	//设置外部中断
	IT0=1;//设置为下降沿触发
	EX0=1;//开启外部中断1
	EA=1;//开启总中断
	PX0=1;//优先级设置为最高
	INT0_input=1;//初始化端口
}

unsigned char IRC_Get_Addr()
{
	return Addr;
}

unsigned char IRC_Get_Command()
{
	return Command;
}


bit Get_Data_Ready_Flag()
{
	if(Data_Ready_Flag){
		Data_Ready_Flag=0;
		return 1;
	}	
	else 
		return 0;
}

bit Get_Repeat_Flag()
{
	if(Repeat_Flag){
		Repeat_Flag=0;
		return 1;
	}
	else 
		return 0;
}

void delay(u16 k) //@10us
{
	while(k--);
}

void IRC_INT0_Routine() interrupt 0
{	
		u16 end;
		u16 counter;
		u8 i;
		u8 j;
	
		//关闭外部中断1，防止二次调用函数
		EX0=0;
		//@9ms的低电平才确定为信号的开始信号
		end=100;				//1000*10us=10ms,超过说明接收到错误的信号
		while((INT0_input==0)&&(end>0))	//等待前面9ms的低电平过去  		
		{			
			delay(10);
			end--;
		}
		
		end=500;
		while((INT0_input==1)&&(end>0))	//等待4.5ms的高电平过去  		
		{			
			delay(1);
			end--;
		} 
			
					for(i=0;i<4;i++)
					{
							for(j=0;j<8;j++)
								{					
									//前560us低电平
									end=60;
									while(INT0_input==0&&end>0)
									{
										delay(1);
										end--;
									}
									end=300;
									counter=0;
									while((INT0_input==1)&&(end>0))	 //计算高电平的时间长度。
									{
										delay(10);	 //0.1ms
										counter++;
										end--;
										if(counter>30)//长时间不再变回低电平，表示为Repeat信号
										{
											counter=0;
											EX0=1;
											Repeat_Flag=1;
											return;
										}
									}
									Data[i]>>=1;	 //i表示第几组数据
									if(counter>=8)			//如果高电平出现大于565us，那么是1
									{
										Data[i]|=0x80;
									}
									counter=0;
													
								}
					}
					if(Data[0]==~Data[1]&&Data[2]==~Data[3])
					{
						Addr=Data[0];
						Command=Data[2];
						Data_Ready_Flag=1;
					}
					EX0=1;
					counter=0;
}