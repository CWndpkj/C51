#include "SPI_helper.h"
typedef unsigned char u8;
typedef unsigned int u16;
/*
SPI_0 ʱ�Ӽ��� 0    ʱ����λ  0
SPI_1 ʱ�Ӽ��� 0    ʱ����λ  1
SPI_2 ʱ�Ӽ��� 1    ʱ����λ  0
SPI_3 ʱ�Ӽ��� 1    ʱ����λ  1
*/
typedef enum SPI_TYPE
{
    SPI_0,SPI_1,SPI_2,SPI_3
}SPI_Type;
//�����������������
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