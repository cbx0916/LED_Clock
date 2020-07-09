#include "SPI.h"
void SPI_595_Init(void)  
{  
 
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);
  GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);        
  //NSS:PB4 SPI_CLOCK:PB5, SPI_MOSI: PB6, SPI_MISO: PB7  
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_High_Slow);  
  GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Slow);  
  //主机模式，配置为输入 该设置很关键  
  GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_In_PU_No_IT); 
  
  /* 初始化SPI */  
  //SPI_Init(SPI1, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_4, SPI_Mode_Master, SPI_CPOL_High, SPI_CPHA_2Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);  
  
  //SPI_Cmd(SPI1, ENABLE);  /* 使能SPI */  
  
  /* 配置CS管脚 */  
  //GPIO_Init(GPIOF , GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);  
  //GPIO_WriteBit(GPIOF, GPIO_Pin_1, SET);     /* 拉高不使能外部SPI设备 */  
}  

void SPI_Send_byte(unsigned char data)  
{  
  for(int ii=0;ii<8;ii++)
  {
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    if(data&0x01)GPIO_SetBits(GPIOB,GPIO_Pin_6);
    else GPIO_ResetBits(GPIOB,GPIO_Pin_6);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);
    data>>=1;
  }
  
 } 

void SPI_595_Send_Time(unsigned char *BUF)
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
  for(int ii=0;ii<6;ii++)
  {
    SPI_Send_byte(*BUF++);
  }
  GPIO_SetBits(GPIOB,GPIO_Pin_4);
  for(int ii=30000;ii>0;ii--);
  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
}