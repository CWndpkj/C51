#include <REGX52.H>
#include "XPT2046.h"
#include "SPI.h"
#include "LCD1602.h"
#define DELTA 0.02

sbit DIN  = P3 ^ 4;
sbit CS   = P3 ^ 5;
sbit DCLK = P3 ^ 6;
sbit DOUT = P3 ^ 7;

/**
 * @brief TODO:加入模拟输入
 */
#define GR1                0xA0
#define NTC1               0xD0
#define AD1                0x90
unsigned char control_byte;
unsigned int out_put_data_12;
unsigned int pre_data_12;
unsigned char out_put_data_8;
bit flush_flag;

/**
 * @brief 初始化函数
 */
void XPT2046_Init()
{
    TMOD &= 0xF0; // 设置定时器模式
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0xFF;   // 设置定时初始值
    TH0 = 0xFF;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    ET0 = 1;      // 使能定时器0中断
    EA  = 1;      // 开启总中断

    DCLK = 0;
    CS   = 1;
}
/**
 * @brief 设置工作的方式
 * @param Mode 采样的分辨率,1为选择8位,0位选择12位
 * @param SER_DFR  输入的方式,1为单端输入,0为差分输入
 * @param PowerSaveMode 低功耗模式选择位,一般选择0即可(范围 0~3)
具体如下
0 0 使能 在两次 A／D 转换之间掉电，下次转换一开始，芯片立即进入完全上电状态，而无
需额外的延时。在这种模式下，YN 开关一直处于 ON 状态
0 1 禁止 参考电压关闭， ADC 打开
1 0 使能 参考电压打开， ADC 关闭
1 1 禁止 芯片处于上电状态，参考电压和 ADC 总是打开
 */
void XPT2046_SetControlByte(unsigned char Mode, unsigned char SER_DFR, unsigned char PowerSaveMode)
{
    if (Mode) {
        control_byte |= 0x08;
    }
    if (SER_DFR) {
        control_byte |= 0x04;
    }
    control_byte |= PowerSaveMode;
}

/**
 * @brief 选择输入设备 
 * @param device_ID (范围 enum Device::    device_GR1, device_NTC1,device_AD1)
 */
void XPT2046_SetDevice(enum Device device_ID)
{
    switch (device_ID) {
        case device_GR1:
            control_byte |= GR1;
            break;
        case device_NTC1:
            control_byte |= NTC1;
            break;
        case device_AD1:
            control_byte |= AD1;
            break;
    }
}

/**
 * @brief 开始模拟采样
 */
void XPT2046_StartAcquire()
{
    CS  = 0;
    TR0 = 1; // 定时器0开始计时
}

/**
 * @brief 停止模拟采样
 */
void XPT2046_StopAquire()
{
    TR0 = 0; // 定时器0停止计时
    CS  = 1;
}

/**
 * @brief 定时器0中断函数
 */
void Timer0Routine() interrupt 1
{
    static unsigned char send_counter = 0;
    static unsigned char out_flag;
    static unsigned char rcv_counter = 16;
    send_counter++;
    TL0 = 0xFF;
    TH0 = 0xFF;
    if (send_counter <= 8) {
        // 写数据
        DIN  = control_byte & (0x80 >> (send_counter - 1));
        DCLK = 1;
        DCLK = 0;
    }
    if (send_counter == 9) {
        out_flag        = 1;
        out_put_data_12 = 0;
    }
    if (out_flag) {
        DCLK = 1;
        DCLK = 0;
        rcv_counter--;
        // 数据读出

        if (DOUT) {
            out_put_data_12 |= 0x8000 >> (15 - rcv_counter);
        }
        if (rcv_counter == 0) {
            rcv_counter = 16;
            out_flag    = 0;
            if (pre_data_12 - out_put_data_12>2||out_put_data_12-pre_data_12>2) {
                flush_flag  = 1;
                pre_data_12 = out_put_data_12;
            }
        }
    }
    if (send_counter == 24) {
        send_counter = 0;
    }
}
/**
 * @brief 获取数字数据
 * @return unsigned int 返回的data
 */
unsigned int XPT2046_GetData()
{
    return out_put_data_12>>4;
}

/**
 * @brief 获取数据是否被刷新的标志位
 * @return bit 刷新标志位
 */
bit XPT2046_GetFlushFlag()
{
    bit temp_flash_flag = flush_flag;
    flush_flag          = 0;
    return temp_flash_flag;
}