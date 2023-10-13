/**
 * @file key.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  扫描按键
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <REGX52.H>
#include "key.h"
#include "delay.h"
/**
 * @brief 扫描按键并获取按下的按键
 * @return unsigned char 返回按下的键值，范围1-4,
 * 						返回0时没有按键被按下
 */
unsigned char Get_Key()
{
	if(P3_1==0)
	{
		while(P3_1=0);
		key=1;
		delayms(1);//这些延时的作用均为消抖
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