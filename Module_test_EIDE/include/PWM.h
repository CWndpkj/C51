#ifndef _PWM_H_
#define _PWM_H_
//*************************
//更改需要进行PWM输出的端口
#define port P1_0
//**************************

/*
@brief PWM输出 
@param retio PWM输出的占空比
@note  将需要进行PWM输出的端口定义为port
*/
void PWM_Init(unsigned int ratio);

#endif