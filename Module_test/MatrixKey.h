#ifndef _MATRIX_KEY_H_
#define _MATRIX_KEY_H_
#include "delay.h"
//返回获取到矩阵按键的坐标位置，由两位组成，分别为行号和列号
//注：当返回值为0时，表示还未按下任何按键
unsigned char GetKey();
#endif