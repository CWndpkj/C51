#include <REGX52.H>
#include "matrixkey.h"
#define KEY_MATRIX_PORT	P1

sbit sp1=P1^4;
sbit sp2=P1^5;
sbit sp3=P1^6;
sbit sp4=P1^7;

unsigned char GetKey()
{  
	    int i;
			static int ret=100;
			for(i=0;i<4;i++)
			{
				switch(i)
				{
					case 0:KEY_MATRIX_PORT=0xFE;break;
					case 1:KEY_MATRIX_PORT=0xFD;break;
					case 2:KEY_MATRIX_PORT=0xFB;break;
					case 3:KEY_MATRIX_PORT=0xF7;break;
				}
				
				if(sp1==0){
					delayms(20);
					while(sp1==0);
					delayms(20);
					ret=(4-i)*10+4;					
					break;
				}
				if(sp2==0){
					delayms(20);
					while(sp2==0);
					delayms(20);
					ret=(4-i)*10+3;	
					break;
				}
				if(sp3==0){
					delayms(20);
					while(sp3==0);
					delayms(20);
					ret=(4-i)*10+2;
					break;
				}
				if(sp4==0){
					delayms(20);
					while(sp4==0);
					delayms(20);
					ret=(4-i)*10+1;
					break;
				}
						
			}
			
			return ret;
}