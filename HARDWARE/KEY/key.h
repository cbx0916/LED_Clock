#ifndef __KEY_H_
#define __KEY_H_

#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

//按键“ADD”端口位置定义
#define KEY_ADD_GPIO_TypeDef GPIOF
#define KEY_ADD_GPIO_PIN GPIO_Pin_4
//按键“VPT”端口位置定义
#define KEY_VPT_GPIO_TypeDef GPIOF
#define KEY_VPT_GPIO_PIN GPIO_Pin_6
//按键“UP”端口位置定义
#define KEY_UP_GPIO_TypeDef GPIOF
#define KEY_UP_GPIO_PIN GPIO_Pin_5
//按键“DOWN”端口位置定义
#define KEY_DOWN_GPIO_TypeDef GPIOF
#define KEY_DOWN_GPIO_PIN GPIO_Pin_7
//按键“SET”端口位置定义
#define KEY_SET_GPIO_TypeDef GPIOC
#define KEY_SET_GPIO_PIN GPIO_Pin_1
//按键“OK”端口位置定义
#define KEY_OK_GPIO_TypeDef GPIOC
#define KEY_OK_GPIO_PIN GPIO_Pin_0

#define    KEY1_Down_FG_SET 0x01
#define    KEY2_Down_FG_SET 0x02
#define    KEY3_Down_FG_SET 0x04

#define    KEY4_Down_FG_SET 0x08
#define    KEY5_Down_FG_SET 0x10
#define    KEY6_Down_FG_SET 0x20

#define    KEY1_Down_FG_RST 0xFE
#define    KEY2_Down_FG_RST 0xFD
#define    KEY3_Down_FG_RST 0xFB

#define    KEY4_Down_FG_RST 0xF7
#define    KEY5_Down_FG_RST 0xEF
#define    KEY6_Down_FG_RST 0xDF

//键值定义
#define KEY_NO  0x00 //无按键按下
#define KEY_ADD  0x01//地址按键(KEY1)
#define KEY_VPT  0x02//阈值按键(KEY2)
#define KEY_UP  0x03//上按键(KEY3)
#define KEY_DOWN  0x04//下按键(KEY4)
#define KEY_SET  0x05//设置按键(KEY5)
#define KEY_OK  0x06//确认按键(KEY6)

extern u8 KeyFlag;

//功能函数声明
u8 KeyDispose(void);//按键处理（返回按键值）
void KeyInit(void);//按键初始化

#endif