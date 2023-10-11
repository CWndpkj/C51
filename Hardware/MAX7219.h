#ifndef _MAX_7219_H_
#define _MAX_7219_H

/**
 * @brief 初始化函数
 * 
 */
void MAX7219_Init();

/**
 * @brief 设置显示的亮度
 * @param Brightness 设置的亮度  范围  0x00~0x0F(1/32~31/32)
 */
void MAX7219_SetBrightness(unsigned char Brightness);


/**
 * @brief 设置显示寄存器的值
 * 
 * @param Digit 段选，即要设置的数据的列
 * @param Data_to_Show  设置的显示数据
 */
void MAX7219_SetData(unsigned char Digit,unsigned char Data_to_Show);

/**
 * @brief 显示函数，在需要显示时调用
 */
void MAX7219_Show();

/**
 * @brief 调试模式。所有的LED将全被点亮
 */
void MAX7219_TestMode();

#endif // !_MAX_7219_H_
