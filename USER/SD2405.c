#include "SD2405.h"
void SD2405_Timer2_Init(void)
{
  //时钟配置
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1分频，向上计数，每10us定时中断一次 
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_Prescaler_16, TIM2_CounterMode_Up, 16*1000);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}