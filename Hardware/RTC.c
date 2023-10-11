#include "DS1302.h"
#include "LCD1602.h"
#include "key.h"
#include "delay.h"
u8 key = 0;
u8 time_set_flag;
char time[7] = {04, 11, 1, 1, 1, 1, 6};
void RTC_Init()
{
    LCD_Init();
    DS1302_Init();
    LCD_ShowString(1, 1, "RTC-Timer:");
    DS1302_SetTime(time);
    LCD_ShowString(1, 15, "Y");
    LCD_ShowString(2, 3, "/");
    LCD_ShowString(2, 6, " ");
    LCD_ShowString(2, 9, ":");
    LCD_ShowString(2, 12, ":");
}
void RTC_Show()
{
    if (time_set_flag) {
        DS1302_SetTime(time);
        time_set_flag = 0;
    }
    LCD_ShowNum(1, 12, DS1302_GetTime()[0], 2);
    LCD_ShowNum(2, 1, DS1302_GetTime()[1], 2);
    LCD_ShowNum(2, 4, DS1302_GetTime()[2], 2);
    LCD_ShowNum(2, 7, DS1302_GetTime()[3], 2);
    LCD_ShowNum(2, 10, DS1302_GetTime()[4], 2);
    LCD_ShowNum(2, 13, DS1302_GetTime()[5], 2);
    LCD_ShowNum(2, 16, DS1302_GetTime()[6], 2);
}

void RTC_Set()
{
    static u8 ratio = 5;
    static u8 j     = 0;
    u8 i;
    static flag                     = 1;
    static unsigned char select_pos = 0;
    j++;
    j %= 30;
    if (flag) {
        for (i = 0; i < 8; i++) {
            time[i] = DS1302_GetTime()[i];
        }
        flag = 0;
    }
    time_set_flag = 0;

    if (key == 2) {
        select_pos++;
        select_pos %= 6;
    }
    if (key == 3) {
        time[select_pos]++;
        time[0] %= 100;
        if (time[1] >= 13) {
            time[1] = 1;
        }
        if (time[0] % 4 == 0 || time[0] % 100 != 0) {
            if (time[1] == 2 && time[2] >= 30) {
                time[2] = 1;
            }
        } else if (time[1] == 2 && time[2] >= 29) {
            time[2] = 1;
        }
        if (time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || time[1] == 8 ||
            time[1] == 10 || time[1] == 12) {
            if (time[2] >= 32) {
                time[2] = 1;
            }
        } else if (time[1] != 2) {
            if (time[2] >= 31) {
                time[2] = 1;
            }
        }
        time[3] %= 24;
        time[4] %= 60;
        time[5] %= 60;
        if (time[6] == 8) {
            time[6] = 1;
        }
    }
    if (key == 4) {
        time[select_pos]--;
        if (time[0] == -1)
            time[0] = 99;
        if (time[1] == 0) {
            time[1] = 12;
        }
        if (time[2] == 0 && time[1] == 2) {
            if (time[0] % 4 == 0 || time[0] % 100 != 0) {
                time[2] = 29;
            } else
                time[2] = 28;
        } else if (time[2] == 0 && (time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || time[1] == 8 ||
                                    time[1] == 10 || time[1] == 12)) {
            time[2] = 31;
        } else if (time[2] == 0) {
            time[2] = 30;
        }
        if (time[6] == 0) {
            time[6] = 7;
        }
        if (time[3] == -1) {
            time[3] = 23;
        }
        if (time[4] == -1) {
            time[4] = 59;
        }
        if (time[5] == -1) {
            time[5] = 59;
        }
    }

    switch (select_pos) {
        case 0:
            if (j > ratio)
                LCD_ShowNum(1, 12, time[0], 2);
            else
                LCD_ShowString(1, 12, "  ");
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 1:
            if (j > ratio)
                LCD_ShowNum(2, 1, time[1], 2);
            else
                LCD_ShowString(2, 1, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 2:
            if (j > ratio)
                LCD_ShowNum(2, 4, time[2], 2);
            else
                LCD_ShowString(2, 4, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 3:
            if (j > ratio)
                LCD_ShowNum(2, 7, time[3], 2);
            else
                LCD_ShowString(2, 7, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 4:
            if (j > ratio)
                LCD_ShowNum(2, 10, time[4], 2);
            else
                LCD_ShowString(2, 10, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 5:
            if (j > ratio)
                LCD_ShowNum(2, 13, time[5], 2);
            else
                LCD_ShowString(2, 13, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 16, time[6], 2);

            break;
        case 6:
            if (j > ratio)
                LCD_ShowNum(2, 16, time[6], 2);
            else
                LCD_ShowString(2, 16, "  ");
            LCD_ShowNum(1, 12, time[0], 2);
            LCD_ShowNum(2, 1, time[1], 2);
            LCD_ShowNum(2, 4, time[2], 2);
            LCD_ShowNum(2, 7, time[3], 2);
            LCD_ShowNum(2, 10, time[4], 2);
            LCD_ShowNum(2, 13, time[5], 2);
            break;
    }
    time_set_flag = 1;
}

void main()
{
    u8 mode = 0;
    RTC_Init();
    while (1) {
        key = Get_Key();
        if (key) {
            if (key == 1) {
                mode++;
                mode %= 2;
            }
        }
        if (mode == 0) {
            RTC_Show();
        } else if (mode == 1) {
            RTC_Set();
        }
    }
}