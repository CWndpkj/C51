#include <REGX52.H>

sbit BEEP=P2^5;	//��P2.5�ܽŶ���ΪBEEP
typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;
sbit LED=P2^6;
//���������λѡ�źſ��ƽ�
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//��������ܶ����
#define SMG_A_DP_PORT P0;

//�������������ʾ0~F�Ķ�������(0-F,����һ��С����)
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x01};

void delay(u8 declipse)   //��λms
{
	while(declipse--)
	{
	    unsigned char a,b,c;
	    for(c=1;c>0;c--)
	        for(b=142;b>0;b--)
	            for(a=2;a>0;a--);
	}
}

//�������ʾ����  (what ʹ�ô�д��
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
//   	while(i--)//ѭ��2000��
//	{
//		LED=!LED;
//		BEEP=!BEEP;//����һ��Ƶ�ʵ������ź�
//		delay(1);
//	}
//	i=0;//����
//	BEEP=0;//�رշ�����
//	LED=1;
		 SMG_display(2,0);
		 delay(100);
	

	}	
}
