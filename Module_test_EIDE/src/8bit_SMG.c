#include <REGX52.H>
#include "8bit_SMG.h"
// 定义数码管位选信号控制脚
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;
// 定义数码管的管段码口
sfr SMG_A_DP_PORT = 0x80;
// 共阴极数码管显示0~F,小数点的段码数据
unsigned char gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                               0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80};

void SMG_display(unsigned char location, unsigned char num_data)
{
    SMG_A_DP_PORT = 0x00;

    LSA = ((~location) >> 0) & 1 == 1;
    LSB = ((~location) >> 1) & 1 == 1;
    LSC = ((~location) >> 2) & 1 == 1;

    switch (num_data) {
        case 0:
            SMG_A_DP_PORT = gsmg_code[0];
            break;
        case 1:
            SMG_A_DP_PORT = gsmg_code[1];
            break;
        case 2:
            SMG_A_DP_PORT = gsmg_code[2];
            break;
        case 3:
            SMG_A_DP_PORT = gsmg_code[3];
            break;
        case 4:
            SMG_A_DP_PORT = gsmg_code[4];
            break;
        case 5:
            SMG_A_DP_PORT = gsmg_code[5];
            break;
        case 6:
            SMG_A_DP_PORT = gsmg_code[6];
            break;
        case 7:
            SMG_A_DP_PORT = gsmg_code[7];
            break;
        case 8:
            SMG_A_DP_PORT = gsmg_code[8];
            break;
        case 9:
            SMG_A_DP_PORT = gsmg_code[9];
            break;
        case 'A':
            SMG_A_DP_PORT = gsmg_code[10];
            break;
        case 'B':
            SMG_A_DP_PORT = gsmg_code[11];
            break;
        case 'C':
            SMG_A_DP_PORT = gsmg_code[12];
            break;
        case 'D':
            SMG_A_DP_PORT = gsmg_code[13];
            break;
        case 'E':
            SMG_A_DP_PORT = gsmg_code[14];
            break;
        case 'F':
            SMG_A_DP_PORT = gsmg_code[15];
            break;
        case '.':
            SMG_A_DP_PORT = gsmg_code[16];
            break;
    }
    delayms(1);
}
void SMG_Show(unsigned int _data)
{
    SMG_display(0, _data / 10000000);
    SMG_display(1, (_data % 10000000) / 1000000);
    SMG_display(2, (_data % 1000000) / 100000);
    SMG_display(3, (_data % 100000) / 10000);
    SMG_display(4, (_data % 10000) / 1000);
    SMG_display(5, (_data % 1000) / 100);
    SMG_display(6, (_data % 100) / 10);
    SMG_display(7, _data % 10);
}