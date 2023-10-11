#ifndef _MATRIXKEY_H_
#define _MATRIXKEY_H_
#include "delay.h"
//返回获取到矩阵按键的坐标位置，由两位组成，分别为行号和列号
//注：当返回值小于100时，为正常值，返回值为100时，表示当前未按下按键
unsigned char GetKey();
#endif