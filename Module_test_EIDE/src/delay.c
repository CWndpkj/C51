#include "delay.h"
//延时函数
void delayms(unsigned int declipse)   
{
	while(declipse--)
	{
			unsigned char a,b,c;
			for(c=1;c>0;c--)
					for(b=142;b>0;b--)
							for(a=2;a>0;a--);
	}
}