/**
 * @file MatrixKey.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  矩阵键盘扫描获取键值
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "MatrixKey.h"
#include <REGX52.H>

#define KEY_MATRIX_PORT P1

sbit sp1 = P1 ^ 4;
sbit sp2 = P1 ^ 5;
sbit sp3 = P1 ^ 6;
sbit sp4 = P1 ^ 7;

/**
 * @brief 返回获取到矩阵按键的坐标位置，由两位组成，分别为行号和列号
 * 		  比如 41 代表第四行,第一列,即 行号=返回值/10, 列号=返回值%10
 * @note：当返回值小于100时，为正常值，返回值为100时，表示当前未按下按键
 * @return unsigned char  返回值
 */
unsigned char GetKey()
{
    int i;
    static unsigned char ret = 0;
    for (i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            KEY_MATRIX_PORT = 0xFE;
            break;
        case 1:
            KEY_MATRIX_PORT = 0xFD;
            break;
        case 2:
            KEY_MATRIX_PORT = 0xFB;
            break;
        case 3:
            KEY_MATRIX_PORT = 0xF7;
            break;
        }

        if (sp1 == 0)
        {
            delayms(20);//消抖
            while (sp1 == 0)
                ;
            delayms(20);
            ret = (4 - i) * 10 + 4;
            break;
        }
        if (sp2 == 0)
        {
            delayms(20);
            while (sp2 == 0)
                ;
            delayms(20);
            ret = (4 - i) * 10 + 3;
            break;
        }
        if (sp3 == 0)
        {
            delayms(20);
            while (sp3 == 0)
                ;
            delayms(20);
            ret = (4 - i) * 10 + 2;
            break;
        }
        if (sp4 == 0)
        {
            delayms(20);
            while (sp4 == 0)
                ;
            delayms(20);
            ret = (4 - i) * 10 + 1;
            break;
        }
    }

    return ret;
}