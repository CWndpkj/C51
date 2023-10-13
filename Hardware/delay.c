/**
 * @file delay.c
 * @author pkjinfinity (pkjinfinity@outlook.com)
 * @brief  延时函数,适用于C51,晶振频率11.059Hz
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "delay.h"

/**
 * @brief 毫秒延时,存在一定的误差
 * @param declipse 延时的时间,单位ms
 */
void delayms(unsigned char declipse)
{
    while (declipse--)
    {
        unsigned char a, b, c;
        for (c = 1; c > 0; c--)
            for (b = 142; b > 0; b--)
                for (a = 2; a > 0; a--)
                    ;
    }
}