#include <REGX52.H>

sbit BEEP=P2^5;	//将P2.5管脚定义为BEEP
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
sbit LED=P2^6;
//定义数码管位选信号控制脚
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//定义数码管段码口
#define SMG_A_DP_PORT P0;

//共阴极数码管显示0~F的段码数据(0-F,加上一个小数点)
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x01};

void delay(u8 declipse)   //单位ms
{
	while(declipse--)
	{
	    unsigned char a,b,c;
	    for(c=1;c>0;c--)
	        for(b=142;b>0;b--)
	            for(a=2;a>0;a--);
	}
}

//数码管显示函数  (what 使用大写）
void SMG_display(u8 where,u8 what)
{
	 u8 mask= 1 << (1 - 1);
	 LSA=(~where)&mask;
	 mask= 1 << (2 - 1);
	 LSB=(~where)&mask;
	 mask= 1 << (3 - 1);
	 LSC=(~where)&mask;
	 switch(what)
	 {
	 	case 0:
		   SMG_A_DP_PORT= gsmg_code[0];break;
		case 1:
		   SMG_A_DP_PORT= gsmg_code[1];break;
		case 2:
		   SMG_A_DP_PORT= gsmg_code[2];break;
		case 3:
		   SMG_A_DP_PORT= gsmg_code[3];break;
		case 4:
		   SMG_A_DP_PORT= gsmg_code[4];break;
		case 5:
		   SMG_A_DP_PORT= gsmg_code[5];break;
		case 6:
		   SMG_A_DP_PORT= gsmg_code[6];break;
		case 7:
		   SMG_A_DP_PORT= gsmg_code[7];break;
		case 8:
		   SMG_A_DP_PORT= gsmg_code[8];break;
		case 9:
		   SMG_A_DP_PORT= gsmg_code[9];break;
		case 'A':
		   SMG_A_DP_PORT= gsmg_code[10];break;
		case 'B':
		   SMG_A_DP_PORT= gsmg_code[11];break;
		case 'C':
		   SMG_A_DP_PORT= gsmg_code[12];break;
		case 'D':
		   SMG_A_DP_PORT= gsmg_code[13];break;
		case 'E':
		   SMG_A_DP_PORT= gsmg_code[14];break;
		case 'F':
		   SMG_A_DP_PORT= gsmg_code[15];break;
		case '.':
			SMG_A_DP_PORT= gsmg_code[16];break;

	 }
}

void main()
{			 
	u16	i=2000;
	while(1)
	{
//   	while(i--)//循环2000次
//	{
//		LED=!LED;
//		BEEP=!BEEP;//产生一定频率的脉冲信号
//		delay(1);
//	}
//	i=0;//清零
//	BEEP=0;//关闭蜂鸣器
//	LED=1;
		 SMG_display(2,0);
		 delay(100);
	

	}	
}
