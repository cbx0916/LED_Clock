#ifndef __LED_H_
#define __LED_H_
#include "stm8l15x_gpio.h"

//LED灯 "LED1"端口位置定义
#define KEY_LED1_GPIO_TypeDef   GPIOG
#define KEY_LED1_GPIO_PIN       GPIO_Pin_0
//按键 "LED2"端口位置定义
#define KEY_LED2_GPIO_TypeDef   GPIOG
#define KEY_LED2_GPIO_PIN       GPIO_Pin_1
//按键 "LED3"端口位置定义
#define KEY_LED3_GPIO_TypeDef   GPIOG
#define KEY_LED3_GPIO_PIN       GPIO_Pin_2

#define LED1 0x01
#define LED2 0x02
#define LED3 0x03


void LedInit(void);//LED初始化
void LedDispose(void);//LED处理

#endif