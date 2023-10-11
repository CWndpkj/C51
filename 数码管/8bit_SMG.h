#ifndef _8BIT_SMG_H_
#define _8BIT_SMG_H_

#include <delay.h>

//动态数码管显示函数  (where，显示在第几个数码管，以0为第一个，what 显示的内容，包括0-F,以及小数点
//注意大写传参)
void SMG_display(unsigned char location,unsigned char what);
#endif