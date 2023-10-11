#include <REGX52.H>
#include "key.h"
#include "Delay.h"

unsigned char Key_Get()
{
	static unsigned char key=0;
	if(P3_1==0)
	{
		while(P3_1==0);
		key=1;
		delayms(1);
	}
	else if(P3_0==0)
		{
		while(P3_0==0);
		key=2;
		delayms(1);
	}
	else if(P3_2==0)
		{
		while(P3_2==0);
		key=3;
		delayms(1);
	}
	else if(P3_3==0)
		{
		while(P3_3==0);
		key=4;
		delayms(1);
	}
	return key;
}