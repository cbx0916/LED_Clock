#include "SD2405.h"
void SD2405_Timer2_Init(void)
{
  //ʱ������
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1��Ƶ�����ϼ�����ÿ10us��ʱ�ж�һ�� 
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_Prescaler_16, TIM2_CounterMode_Up, 16*1000);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}