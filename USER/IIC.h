#ifndef _IIC_H__
#define _IIC_H__


#include "stm8l15x.h"

void Delay();
void Sim_IIC_init(void);

void IIC_SDA_DDR(unsigned char ddr);
void IIC_START(void);
void IIC_STOP(void);
char I2CWaitAck(void);
void I2CSendByte(unsigned char demand);
void WriteTimeOn(void);
void WriteTimeOff(void);
void I2CWriteDate(unsigned char *BUF);

unsigned char IIC_Write8bit(unsigned char DAT);
unsigned char IIC_Read8BitACK(void);
unsigned char IIC_Read8BitNACK(void);

void SD2405_Read7Byte(unsigned char *BUF);
void SD2405_WriteNByte(unsigned char *BUF,unsigned char ADDR,unsigned char LEN);
#endif