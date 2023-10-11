#include "LCD1602.h"
#include "24C02.h"
#include "delay.h"
#include "REGX52.H"
#include "OLED.h"
#include "MAX7219.h"
#include "XPT2046.h"

void main()
{
    // OLED_Init();

    /*MAX7219_Init();

    MAX7219_SetData(0, 0x00);
    MAX7219_SetData(1, 0xAA);
    MAX7219_Show();
    while (1) {
        MAX7219_SetBrightness(0x00);
        delayms(1000);
        MAX7219_SetData(0,0x20);
        MAX7219_SetBrightness(0x0F);
        delayms(2000);
        MAX7219_SetData(0,0x10);
    }
    */

    LCD_Init();
    XPT2046_Init();
    XPT2046_SetControlByte(0,1,0);
    XPT2046_SetDevice(device_AD1);
    XPT2046_StartAcquire();
    while (1) {
        
        LCD_ShowBinNum(1,1,XPT2046_ReadAD(0x9C),12);
        //LCD_ShowHexNum(1,1,XPT2046_GetData(),4);
    }
}