/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "IIC.h"
#include "SPI.h"
#include "UART.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


char num_time[6]={0};
unsigned char dgt_time[6]={0};
unsigned char dgt_timep[6]={0};//test
unsigned char get_bcd_tim[7]={0};
unsigned char write_data[7]={0x20,0x19,0x95,0x06,0x04,0x07,0x20};
unsigned char dgt2num[10]={0xfd,0x31,0xdb,0x7b,0x37,0x6f,0xef,0x39,0xff,0x7f};//
unsigned char dgt2nump[10]={0xfc,0x30,0xda,0x7a,0x36,0x6e,0xee,0x38,0xfe,0x7e};
int tim=0;

unsigned char time_now[7]={0x20,0x19,0x95,0x06,0x04,0x07,0x20};//2020年07月 04日 周06 15：19：20
void Update_time();
void delay();
void main(void)
{
  
  
  Sim_IIC_init();
  USART1_Init();
  SPI_595_Init();
  
//  WriteTimeOn();//开启写时间
//  I2CWriteDate(time_now);//写入现在时间
//  WriteTimeOff();//关闭写时间
  
  while(1)
  {
    USART_ACK();
    Update_time();
    
  }
}

//10进制
char bcd_decimal(unsigned char bcd)
{
  return bcd-(bcd >> 4)*6;
}

void Update_time()
{
  SD2405_Read7Byte(get_bcd_tim);
  
  if(*(get_bcd_tim+2)>(0x25))
   *(get_bcd_tim+2)-=(0x80);//24小时制的转换

  for(int ii=1;ii<3;ii++)
  {
    num_time[ii*2]=bcd_decimal(*(get_bcd_tim+ii))%10;//个位
    num_time[ii*2+1]=bcd_decimal(*(get_bcd_tim+ii))/10;//十位
    dgt_time[ii*2]=dgt2num[num_time[ii*2]];
    dgt_time[ii*2+1]=dgt2num[num_time[ii*2+1]];
    
    dgt_timep[ii*2]=dgt2nump[num_time[ii*2]];//test
    dgt_timep[ii*2+1]=dgt2nump[num_time[ii*2+1]];//test
  }
//  tim++;//
//  if(tim>10)//
//  {
//    SPI_595_Send_Time(dgt_timep);//
//    tim=0;//
//  }
  
  tim++;//
  if(tim>10)//
  {
    SPI_595_Send_Time(dgt_timep);//
     if(tim>11)//
       tim=0;//
  }
  else//
  SPI_595_Send_Time(dgt_time);
}
void delay()
{
  for(int i=1000;i>0;i--)
    ;
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
