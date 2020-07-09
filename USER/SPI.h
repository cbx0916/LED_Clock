#ifndef _SPI_H_
#define _SPI_H_
#include "stm8l15x.h"
void SPI_595_Init(void);
void SPI_Send_byte(unsigned char data);
void SPI_595_Send_Time(unsigned char * BUF);
#endif