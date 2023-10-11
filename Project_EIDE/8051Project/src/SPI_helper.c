#include "SPI_helper.h"
typedef unsigned char u8;
typedef unsigned int u16;
/*
SPI_0 时钟极性 0    时钟相位  0
SPI_1 时钟极性 0    时钟相位  1
SPI_2 时钟极性 1    时钟相位  0
SPI_3 时钟极性 1    时钟相位  1
*/
typedef enum SPI_TYPE
{
    SPI_0,SPI_1,SPI_2,SPI_3
}SPI_Type;
//发送数据与接收数据
void SPI_Init(SPI_Type type)
{
    switch (type)
    {
    case SPI_0:
    {
        
        break;
    }
       
    
    default:
        break;
    }
}