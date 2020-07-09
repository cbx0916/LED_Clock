#include "key.h"


u8 KeyDispose(void);//按键处理（返回按键值）
void KeyInit(void);//按键初始化

u8 KeyFlag;//按键按下标志，如果有按键按下，对应位标志立，按键释放时，返回按键值


//*************功能函数实现**************


/*
函数名称：按键初始化函数
入口参数：无
返回参数：无
*/
void KeyInit(void)//按键初始化
{
    //将所有按键均设置为输入
    GPIO_Init(KEY_ADD_GPIO_TypeDef, KEY_ADD_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"ADD"按键 KEY1
    GPIO_Init(KEY_VPT_GPIO_TypeDef, KEY_VPT_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"VPT"按键 KEY2
    GPIO_Init(KEY_UP_GPIO_TypeDef, KEY_UP_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"UP"按键 KEY3
    GPIO_Init(KEY_DOWN_GPIO_TypeDef, KEY_DOWN_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"DOWN"按键 KEY4
    GPIO_Init(KEY_SET_GPIO_TypeDef, KEY_SET_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"SET"按键 KEY5
    GPIO_Init(KEY_OK_GPIO_TypeDef, KEY_OK_GPIO_PIN, GPIO_Mode_In_PU_No_IT);//初始化"OK"按键 KEY6
}

u8 KeyDispose(void)//按键处理（返回按键值）
{   
    u8 keyNum = KEY_NO; //按键键值零时变量
    if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4))//读取IO口电平，判断并处理
    {
        if(!KeyFlag&&KEY1_Down_FG_SET)//之前没有按下
        {
            KeyFlag = KeyFlag||KEY1_Down_FG_SET;//立按下标志
        }              
    }
    else    //读取到高电平，判断是否为按键释放
    {
        if(KeyFlag&&KEY1_Down_FG_SET)//如果之前有按键按下标志，现在检测为按键释放
        {
            KeyFlag = KeyFlag&&KEY1_Down_FG_RST;//清按下标志   
            keyNum = KEY_ADD;   //"地址"按键被按下 ---KEY1
        }
    }
        
    if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6))
    {
        keyNum = KEY_VPT;   //"阈值"按键被按下---KEY2
    }
    
    if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5))
    {
        keyNum = KEY_UP;   //"上"按键被按下---KEY3
    }
    
    if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7))
    {
        keyNum = KEY_DOWN;//"下"按键被按下---KEY4
    }
    
    
    if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))
    {
        keyNum = KEY_SET;//"设置"按键被按下---KEY5
    }
    
    if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
    {
        keyNum = KEY_OK;//"OK"按键被按下---KEY6
    }    
    return keyNum;   
}