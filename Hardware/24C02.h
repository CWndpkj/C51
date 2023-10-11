#ifndef _24C02_H_
#define _24C02_H_

/**
 * @brief AT24c02写byte
 * @param byte_data 要写的byte数据
 * @param addr      写入的数地址，范围  0x00~0xFF
 */
void _24C02_WriteByte(unsigned char byte_data, unsigned char addr);

/**
 * @brief AT24c02随机读一个byte
 * @param addr 要从何处读取byte
 * @return unsigned 读取出的byte
 */
unsigned char _24C02_ReadByte(unsigned char addr);

#endif // !24C02_H_
