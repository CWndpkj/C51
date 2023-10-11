#ifndef _XPT2046_H_
#define _XPT2046_H_
enum Device {
    device_GR1,
    device_NTC1,
    device_AD1
};
void XPT2046_Init();
/**
 * @brief 设置工作的方式
 * @param Mode 采样的分辨率,1为选择8位,0位选择12位
 * @param SER_DFR  输入的方式,1为单端输入,0为差分输入
 * @param PowerSaveMode 低功耗模式选择位,具体如下
0 0 使能 在两次 A／D 转换之间掉电，下次转换一开始，芯片立即进入完全上电状态，而无
需额外的延时。在这种模式下，YN 开关一直处于 ON 状态
0 1 禁止 参考电压关闭， ADC 打开
1 0 使能 参考电压打开， ADC 关闭
1 1 禁止 芯片处于上电状态，参考电压和 ADC 总是打开
 */
void XPT2046_SetControlByte(unsigned char Mode, unsigned char SER_DFR, unsigned char PowerSaveMode);

void XPT2046_SetDevice(enum Device device_ID);

void XPT2046_StartAcquire();

void XPT2046_StopAquire();

unsigned int XPT2046_GetData();

unsigned int XPT2046_ReadAD(unsigned char Command);

bit XPT2046_GetFlushFlag();
#endif // !_XPT