#include <REGX52.H>
#include "key.h"
#include "delay.h"

unsigned char Get_Key()
{
	if(P3_1==0)
	{
		while(P3_1=0);
		key=1;
		delayms(1);
		return 1;
	}
	else if(P3_0==0)
		{
		while(P3_0=0);
		key=2;
		delayms(1);
		return 2;
	}
	else if(P3_2==0)
		{
		while(P3_2=0);
		key=3;
		delayms(1);
		return 3;
	}
	else if(P3_3==0)
		{
		while(P3_3=0);
		key=4;
		delayms(1);
		return 4;
	}
	else
		return 0;
}