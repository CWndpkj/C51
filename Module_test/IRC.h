#ifndef _IRC_H_
#define _IRC_H_

void IRC_Init();

//获取数据位Ready Flag
bit Get_Data_Ready_Flag();
//获取Rpeteat Flag
bit Get_Repeat_Flag();
//获取地址
unsigned char IRC_Get_Addr();
//获取命令
unsigned char IRC_Get_Command();

#endif