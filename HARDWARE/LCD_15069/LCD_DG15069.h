#ifndef __STM8l052R8_DG15069_H_
#define __STM8l052R8_DG15069_H_

#include "stm8l15x_lcd.h"
/*
//最上方通道号对应RAM区地址
typedef enum
{
    LCD_NUM_1_RAM = LCD->RAM[LCD_RAMRegister_0],
    LCD_NUM_2_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_3_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_4_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_5_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_6_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_7_RAM = LCD->RAM[LCD_RAMRegister_],
    LCD_NUM_8_RAM = LCD->RAM[LCD_RAMRegister_0]
}LCD_NUM_1_8_RAM_TypeDef;
//最上方通道号对所在位地址，例如"1"在 LCD_NUM_1_RAM 的第0x04位置
typedef enum
{
    LCD_NUM_1_BIT  = 0x04, 
    LCD_NUM_2_BIT  = 0x04,
    LCD_NUM_3_BIT  = 0x04,
    LCD_NUM_4_BIT  = 0x04,
    LCD_NUM_5_BIT  = 0x40,
    LCD_NUM_6_BIT  = 0x40,
    LCD_NUM_7_BIT  = 0x40,
    LCD_NUM_8_BIT  = 0x40
}LCD_NUM_1_8_BIT_TypeDef;


//报警指示对应RAM区地址
typedef enum
{
    LCD_FIRE_T1_RAM  = LCD->RAM[LCD_RAMRegister_0] 
    LCD_FIRE_T2_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T3_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T4_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T5_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T6_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T7_RAM  = LCD->RAM[LCD_RAMRegister_]
    LCD_FIRE_T8_RAM  = LCD->RAM[LCD_RAMRegister_0]
}LCD_FIRE_T1_T8_RAM_TypeDef;
//报警指示所在位地址
typedef enum
{
    LCD_FIRE_T1_BIT  = 0x02, 
    LCD_FIRE_T2_BIT  = 0x02,
    LCD_FIRE_T3_BIT  = 0x02,
    LCD_FIRE_T4_BIT  = 0x02,
    LCD_FIRE_T5_BIT  = 0x10,
    LCD_FIRE_T6_BIT  = 0x10,
    LCD_FIRE_T7_BIT  = 0x10,
    LCD_FIRE_T8_BIT  = 0x10   
}LCD_FIRE_T1_T8_BIT_TypeDef;

//故障指示对应RAM区地址
typedef enum
{
    LCD_FAULT_T11_RAM  = LCD->RAM[LCD_RAMRegister_0], 
    LCD_FAULT_T12_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T13_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T14_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T15_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T16_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T17_RAM  = LCD->RAM[LCD_RAMRegister_],
    LCD_FAULT_T18_RAM  = LCD->RAM[LCD_RAMRegister_0]   
}LCD_FAULT_T11_T18_RAM_TypeDef;
//故障指示所在位地址
typedef enum
{
    LCD_FAULT_T11_BIT  = 0x01, 
    LCD_FAULT_T12_BIT  = 0x01,
    LCD_FAULT_T13_BIT  = 0x01,
    LCD_FAULT_T14_BIT  = 0x01,
    LCD_FAULT_T15_BIT  = 0x08,
    LCD_FAULT_T16_BIT  = 0x08,
    LCD_FAULT_T17_BIT  = 0x08,
    LCD_FAULT_T18_BIT  = 0x08   
}LCD_FAULT_T11_T18_BIT_TypeDef;

*/


//最上方通道号对应RAM区地址
#define LCD_NUM_1_RAM   LCD->RAM[LCD_RAMRegister_0] 
#define LCD_NUM_2_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_3_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_4_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_5_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_6_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_7_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_NUM_8_RAM   LCD->RAM[LCD_RAMRegister_0]
//最上方通道号对所在位地址
#define LCD_NUM_1_BIT  0x04
#define LCD_NUM_2_BIT  0x04
#define LCD_NUM_3_BIT  0x04
#define LCD_NUM_4_BIT  0x04
#define LCD_NUM_5_BIT  0x40
#define LCD_NUM_6_BIT  0x40
#define LCD_NUM_7_BIT  0x40
#define LCD_NUM_8_BIT  0x40

//报警指示对应RAM区地址
#define LCD_FIRE_T1_RAM   LCD->RAM[LCD_RAMRegister_0] 
#define LCD_FIRE_T2_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T3_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T4_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T5_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T6_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T7_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FIRE_T8_RAM   LCD->RAM[LCD_RAMRegister_0]
//报警指示所在位地址
#define LCD_FIRE_T1_BIT   0x02 
#define LCD_FIRE_T2_BIT   0x02
#define LCD_FIRE_T3_BIT   0x02
#define LCD_FIRE_T4_BIT   0x02
#define LCD_FIRE_T5_BIT   0x10
#define LCD_FIRE_T6_BIT   0x10
#define LCD_FIRE_T7_BIT   0x10
#define LCD_FIRE_T8_BIT   0x10 
//故障指示对应RAM区地址
#define LCD_FAULT_TT1_RAM   LCD->RAM[LCD_RAMRegister_0] 
#define LCD_FAULT_TT2_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT3_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT4_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT5_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT6_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT7_RAM   LCD->RAM[LCD_RAMRegister_]
#define LCD_FAULT_TT8_RAM   LCD->RAM[LCD_RAMRegister_0]
//故障指示所在位地址
#define LCD_FAULT_T11_BIT  0x01 
#define LCD_FAULT_T12_BIT  0x01
#define LCD_FAULT_T13_BIT  0x01
#define LCD_FAULT_T14_BIT  0x01
#define LCD_FAULT_T15_BIT  0x08
#define LCD_FAULT_T16_BIT  0x08
#define LCD_FAULT_T17_BIT  0x08
#define LCD_FAULT_T18_BIT  0x08 

/*
    以下指示 单独控制，不设计专用设置函数
*/
//汉字"地址"对应RAM区地址
#define LCD_ADD_HZ_T9_RAM   LCD->RAM[LCD_RAMRegister_]

//汉字"阈值"对应RAM区地址
#define LCD_VPT_HZ_T10_RAM   LCD->RAM[LCD_RAMRegister_0]

//汉字"故障报警"对应RAM区地址
#define LCD_FAULT_FIRE_HZ_T19_RAM   LCD->RAM[LCD_RAMRegister_1] 

//温度单位"℃"对应RAM区地址
#define LCD_TEMP_UNIT_T20_RAM   LCD->RAM[LCD_RAMRegister_]

//电压单位"V"对应RAM区地址
#define LCD_V_UNIT_T21_RAM   LCD->RAM[LCD_RAMRegister_]

//电流单位"A"对应RAM区地址
#define LCD_A_UNIT_T23_RAM   LCD->RAM[LCD_RAMRegister_0]

//电流单位"m"对应RAM区地址
#define LCD_M_UNIT_T22_RAM   LCD->RAM[LCD_RAMRegister_]



#define LCD_FIRE_SET(N)
#define LCD_FIRE_CLEAR(N)
#define LCD_FAULT_SET(N) 
#define LCD_FAULT_CLEAR(N) 


/*功能函数声明*/
void DG15069Init(void);//段式液晶初始化
void ShowLcdAll(void);//点亮LCD所有区域
void ShowNum(u8 Num);  //显示上方通道号信息
void ClearNum(u8 Num);  //清除上方某通道号信息
void ShowFire(u8 fireNum);  //显示某通道火警信息
void ClearFire(u8 fireNum);  //清除某通道火警信息
void ShowFault(u8 faultNum);//显示某通道故障信息
void ClearFault(u8 faultNum);//清除某通道故障信息


void ShowData(u8 chDat,u8 dat);//更新显示通道号和数据
void SetParameter(void);//设置参数界面，5S后自动退出
void SetADD(void);//设置地址界面
void SetTempVPT(void);//设置温度阈值界面
void SetLeakVPT(void);//设置漏电流阈值界面




#endif
