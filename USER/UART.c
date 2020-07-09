#include "UART.h"
#include "IIC.h"
unsigned char uart_rx_buf[40]={0};
unsigned char uart_tx_buf[40]={0};
extern unsigned char get_bcd_tim[7];
extern unsigned char write_data[7];
USART_WordLength_TypeDef UART1_Length;
USART_Parity_TypeDef UART1_Parity;
USART_StopBits_TypeDef UART1_StopBits;
unsigned long UART1_BAUD=0;
int uart_num=0;
unsigned char uart_ack=0;
unsigned char cs_rx_num=0;
unsigned char cs_tx_num=0;

unsigned char Equipment_ID[4]={0x12,0x34,0x56,0x78};
unsigned char Hardware_Version[2]={0x01,0x02};
unsigned char Software_Version[2]={0x01,0x02};
unsigned char Releast_Time[20]={0x29,0x12,0x20,0x18,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void USART_ACK(void)
{
  
  //如果起始字符不是0x54则认为接收数据错误 清空接收缓存区
  if(uart_num>=1&&uart_rx_buf[0]!=0x54)
  {
    for(int ii=0;ii<40;ii++)uart_rx_buf[ii]=0;
    uart_num=0;
    uart_ack=0;
    return;
  }
  //判断数据是否接收完毕
  if((uart_num!=0)&&(uart_ack==0)&&(uart_num==(11+uart_rx_buf[8])))uart_ack=1;
  if(uart_ack==1)
  {
    disableInterrupts();
    if((uart_rx_buf[2]==Equipment_ID[0])&&(uart_rx_buf[3]==Equipment_ID[1])&&(uart_rx_buf[4]==Equipment_ID[2])&&(uart_rx_buf[5]==Equipment_ID[3]))uart_ack=2;//2表示设备符合需要应答
    else if((uart_rx_buf[2]==0xff)&&(uart_rx_buf[3]==0xff)&&(uart_rx_buf[4]==0xff)&&(uart_rx_buf[5]==0xff))uart_ack=3;//3表示广播需要应答
    else if((uart_rx_buf[2]==0xee)&&(uart_rx_buf[3]==0xee)&&(uart_rx_buf[4]==0xee)&&(uart_rx_buf[5]==0xee))uart_ack=4;//4表示广播不需要应答
    for(int ii=0;ii<(uart_num-2);ii++)cs_rx_num+=uart_rx_buf[ii];
    if((uart_ack==2)||(uart_ack==3))
    {
      if(uart_rx_buf[7]==0x01)                  //读取设备信息
      {
        if(cs_rx_num==uart_rx_buf[uart_num-2]) //正常应答
        {
          uart_tx_buf[0]=0x54;
          uart_tx_buf[1]=0x00;
          uart_tx_buf[2]=Equipment_ID[0];
          uart_tx_buf[3]=Equipment_ID[1];
          uart_tx_buf[4]=Equipment_ID[2];
          uart_tx_buf[5]=Equipment_ID[3];
          uart_tx_buf[6]=0x80;
          uart_tx_buf[7]=0x01;
          uart_tx_buf[8]=0x1b;
          uart_tx_buf[9]=0x00;
          uart_tx_buf[10]=0x00;
          uart_tx_buf[11]=0x01;
          uart_tx_buf[12]=Hardware_Version[0];//硬件版本
          uart_tx_buf[13]=Hardware_Version[1];
          uart_tx_buf[14]=Software_Version[0];//软件版本
          uart_tx_buf[15]=Software_Version[1];
          for(int ii=0;ii<20;ii++)uart_tx_buf[ii+16]=Releast_Time[ii];
          for(int ii=0;ii<36;ii++)cs_tx_num+=uart_tx_buf[ii];
          uart_tx_buf[36]=cs_tx_num;
          uart_tx_buf[37]=0x16;
          for(int ii=0;ii<38;ii++)
          {
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
            USART_SendData8(USART1,*(uart_tx_buf+ii));
          }
        }
        else                                  //异常应答
        {
          uart_tx_buf[0]=0x54;
          uart_tx_buf[1]=0x00;
          uart_tx_buf[2]=Equipment_ID[0];
          uart_tx_buf[3]=Equipment_ID[1];
          uart_tx_buf[4]=Equipment_ID[2];
          uart_tx_buf[5]=Equipment_ID[3];
          uart_tx_buf[6]=0xa0;
          uart_tx_buf[7]=0x01;
          uart_tx_buf[8]=0x03;
          uart_tx_buf[9]=0x00;
          uart_tx_buf[10]=0x00;
          uart_tx_buf[11]=0x01;
          for(int ii=0;ii<12;ii++)cs_tx_num+=uart_tx_buf[ii];
          uart_tx_buf[12]=cs_tx_num;
          uart_tx_buf[13]=0x16;
          for(int ii=0;ii<14;ii++)
          {
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
            USART_SendData8(USART1,*(uart_tx_buf+ii));
          }
        }
      }
      else if((uart_rx_buf[7]==0x02)&&(uart_ack==2))             //写设备ID
      {
        if(cs_rx_num==uart_rx_buf[uart_num-2])
        {
          uart_tx_buf[0]=0x54;
          uart_tx_buf[1]=0x00;
          uart_tx_buf[2]=Equipment_ID[0];
          uart_tx_buf[3]=Equipment_ID[1];
          uart_tx_buf[4]=Equipment_ID[2];
          uart_tx_buf[5]=Equipment_ID[3];
          uart_tx_buf[6]=0xc0;
          uart_tx_buf[7]=0x02;
          uart_tx_buf[8]=0x02;
          uart_tx_buf[9]=0x00;
          uart_tx_buf[10]=0x00;
          for(int ii=0;ii<11;ii++)cs_tx_num+=uart_tx_buf[ii];
          uart_tx_buf[11]=cs_tx_num;
          uart_tx_buf[12]=0x16;
          for(int ii=0;ii<13;ii++)
          {
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
            USART_SendData8(USART1,*(uart_tx_buf+ii));
          }
          for(int ii=0;ii<4;ii++)Equipment_ID[ii]=uart_rx_buf[9+ii];//修改设备ID
        }
        else                                    //写设备ID错误应答保留
        {}
      }
      else if(uart_rx_buf[7]==0x03)
      {
        if(cs_rx_num==uart_rx_buf[uart_num-2])
        {
          if(uart_rx_buf[6]==0x00)
          {
            uart_tx_buf[0]=0x54;
            uart_tx_buf[1]=0x00;
            uart_tx_buf[2]=Equipment_ID[0];
            uart_tx_buf[3]=Equipment_ID[1];
            uart_tx_buf[4]=Equipment_ID[2];
            uart_tx_buf[5]=Equipment_ID[3];
            uart_tx_buf[6]=0x80;
            uart_tx_buf[7]=0x03;
            uart_tx_buf[8]=0xa0;
            uart_tx_buf[9]=0x00;
            uart_tx_buf[10]=0x00;
            SD2405_Read7Byte(get_bcd_tim);
            for(int ii=0;ii<7;ii++)uart_tx_buf[11+ii]=get_bcd_tim[ii];
            for(int ii=0;ii<18;ii++)cs_tx_num+=uart_tx_buf[ii];
            uart_tx_buf[18]=cs_tx_num;
            uart_tx_buf[19]=0x16;
            for(int ii=0;ii<20;ii++)
            {
              while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
              USART_SendData8(USART1,*(uart_tx_buf+ii));
            }
          }
          else if(uart_rx_buf[6]==0x40)
          {
            uart_tx_buf[0]=0x54;
            uart_tx_buf[1]=0x00;
            uart_tx_buf[2]=Equipment_ID[0];
            uart_tx_buf[3]=Equipment_ID[1];
            uart_tx_buf[4]=Equipment_ID[2];
            uart_tx_buf[5]=Equipment_ID[3];
            uart_tx_buf[6]=0xc0;
            uart_tx_buf[7]=0x03;
            uart_tx_buf[8]=0x02;
            uart_tx_buf[9]=0x00;
            uart_tx_buf[10]=0x00;
            for(int ii=0;ii<11;ii++)cs_tx_num+=uart_tx_buf[ii];
            uart_tx_buf[11]=cs_tx_num;
            uart_tx_buf[12]=0x16;
            for(int ii=0;ii<13;ii++)
            {
              while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
              USART_SendData8(USART1,*(uart_tx_buf+ii));
            }
            for(int ii=0;ii<7;ii++)write_data[ii]=uart_rx_buf[9+ii];
            I2CWriteDate(write_data);
          }
        }
        else
        {}
      }
      else if(uart_rx_buf[7]==0x04);
      else if(uart_rx_buf[7]==0x05);
      else if(uart_rx_buf[7]==0x06);
      else if(uart_rx_buf[7]==0x07)
      {
        if(cs_rx_num==uart_rx_buf[uart_num-2])
        {
          uart_tx_buf[0]=0x54;
          uart_tx_buf[1]=0x00;
          uart_tx_buf[2]=Equipment_ID[0];
          uart_tx_buf[3]=Equipment_ID[1];
          uart_tx_buf[4]=Equipment_ID[2];
          uart_tx_buf[5]=Equipment_ID[3];
          uart_tx_buf[6]=0xc0;
          uart_tx_buf[7]=0x07;
          uart_tx_buf[8]=0x02;
          uart_tx_buf[9]=0x00;
          uart_tx_buf[10]=0x00;
          for(int ii=0;ii<11;ii++)cs_tx_num+=uart_tx_buf[ii];
          uart_tx_buf[11]=cs_tx_num;
          uart_tx_buf[12]=0x16;
          for(int ii=0;ii<13;ii++)
           {
             while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));
             USART_SendData8(USART1,*(uart_tx_buf+ii));
           }
          
          if(uart_rx_buf[14]==0x09)UART1_Length=USART_WordLength_9b;
          else UART1_Length=USART_WordLength_8b;
          if(uart_rx_buf[15]==0x01)UART1_StopBits=USART_StopBits_1;
          else UART1_StopBits=USART_StopBits_2;
          if(uart_rx_buf[16]==0x00)UART1_Parity=USART_Parity_No;
          else if(uart_rx_buf[16]==0x01)UART1_Parity=USART_Parity_Even;
          else if(uart_rx_buf[16]==0x02)UART1_Parity=USART_Parity_Odd;
          UART1_BAUD=0;
          UART1_BAUD+=uart_rx_buf[13];
          for(int ii=0;ii<3;ii++)
          {
            UART1_BAUD<<=8;
            UART1_BAUD+=uart_rx_buf[12-ii];
            
          }
          USART_Init(USART1,(uint32_t)UART1_BAUD,UART1_Length,UART1_StopBits,UART1_Parity,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
        }
        else
        {}
        
      }
    }
    else if(uart_ack==4) //广播切不需要应答
    {
      if((uart_rx_buf[7]==0x03)&&(cs_rx_num==uart_rx_buf[uart_num-2]))
      {
        if(uart_rx_buf[6]==0x40)
        {
          for(int ii=0;ii<7;ii++)write_data[ii]=uart_rx_buf[9+ii];
          I2CWriteDate(write_data);
        }
      }
      else if((uart_rx_buf[7]==0x07)&&(cs_rx_num==uart_rx_buf[uart_num-2]))
      {
        if(uart_rx_buf[14]==0x09)UART1_Length=USART_WordLength_9b;
        else UART1_Length=USART_WordLength_8b;
        if(uart_rx_buf[15]==0x01)UART1_StopBits=USART_StopBits_1;
        else UART1_StopBits=USART_StopBits_2;
        if(uart_rx_buf[16]==0x00)UART1_Parity=USART_Parity_No;
        else if(uart_rx_buf[16]==0x01)UART1_Parity=USART_Parity_Even;
        else if(uart_rx_buf[16]==0x02)UART1_Parity=USART_Parity_Odd;
        UART1_BAUD=0;
        UART1_BAUD+=uart_rx_buf[13];
        for(int ii=0;ii<3;ii++)
        {
          UART1_BAUD<<=8;
          UART1_BAUD+=uart_rx_buf[12-ii];   
        }
        USART_Init(USART1,(uint32_t)UART1_BAUD,UART1_Length,UART1_StopBits,UART1_Parity,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
      }
    }
    for(int ii=0;ii<40;ii++)
    {
      uart_rx_buf[ii]=0;
      uart_tx_buf[ii]=0;
    }
    uart_num=0;
    uart_ack=0;
    cs_rx_num=0;
    cs_tx_num=0;
    enableInterrupts();
    
  }
  
}

void USART1_Init(void)
{
  //GPIO_Init(GPIOC,GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);
  //GPIO_Init(GPIOC,GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
  USART_DeInit(USART1);
  USART_Init(USART1,(uint32_t)9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  ITC_SetSoftwarePriority(USART1_RX_IRQn,ITC_PriorityLevel_0);
  enableInterrupts();
  USART_Cmd(USART1, ENABLE);
}