#include "IIC.h"
#include "SD2405.h"
#define IIC_SDA_GPIO_Pin GPIO_Pin_0
#define IIC_SCL_GPIO_Pin GPIO_Pin_1
#define IIC_GPIOx GPIOC


#define SDA_1 GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin)
#define SDA_0 GPIO_ResetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin)
#define SCL_1 GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin)
#define SCL_0 GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin)
#define SDA   GPIO_ReadInputDataBit(IIC_GPIOx,IIC_SDA_GPIO_Pin)

void Delay()
{
  for(int ii=10;ii>0;ii--);
}




//使用软件模拟IIC //PC0--SDA PC1---SCL
//初始化

void Sim_IIC_init(void)
{
GPIO_Init(IIC_GPIOx, IIC_SDA_GPIO_Pin, GPIO_Mode_Out_PP_High_Slow);
GPIO_Init(IIC_GPIOx, IIC_SCL_GPIO_Pin, GPIO_Mode_Out_PP_High_Slow);
}

//SDA引脚方向配置
void IIC_SDA_DDR(unsigned char ddr)
{
  if(ddr)
  {
    GPIO_Init(IIC_GPIOx,IIC_SDA_GPIO_Pin,GPIO_Mode_Out_PP_High_Slow);
    
  }
  else
  {
    GPIO_Init(IIC_GPIOx,IIC_SDA_GPIO_Pin,GPIO_Mode_In_PU_No_IT);
  }
}

//IIC总线起始信号
void IIC_START(void)
{
  IIC_SDA_DDR(1);
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_ResetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
}

//IIC总线终止信号
void IIC_STOP(void)
{
  IIC_SDA_DDR(1);
  GPIO_ResetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  
}


char I2CWaitAck(void)
{
  SCL_0;
  SDA_1;
  Delay();
  IIC_SDA_DDR(0);
  SCL_1;
  Delay();
  
  while(SDA)
  {
    SCL_0;
    return 0;
    
  }
  SCL_0;
  return 1;
}
void I2CSendByte(unsigned char demand)
{
  unsigned char i=8;
  IIC_SDA_DDR(1);
  while(i--)
  {
    SCL_0;
    Delay();
    if(demand&0x80)SDA_1;
    else SDA_0;
    demand<<=1;
    SCL_1;
    Delay();
  }
  SCL_0;
}
void WriteTimeOn(void)
{
  IIC_START();
  I2CSendByte(0x64);
  I2CWaitAck();
  I2CSendByte(0x10);//设置写地址10H      
  I2CWaitAck();	
  I2CSendByte(0x80);//置WRTC1=1      
  I2CWaitAck();
  IIC_STOP(); 
  IIC_START();
  I2CSendByte(0x64);      
	I2CWaitAck();   
        I2CSendByte(0x0F);//设置写地址0FH      
	I2CWaitAck();	
	I2CSendByte(0x84);//置WRTC2,WRTC3=1      
	I2CWaitAck();
	IIC_STOP();
}
void WriteTimeOff(void)
{		
	IIC_START();
	I2CSendByte(0x64); 
        
	I2CWaitAck();
        I2CSendByte(0x0F);//设置写地址0FH      
	I2CWaitAck();	
	I2CSendByte(0x0) ;//置WRTC2,WRTC3=0      
	I2CWaitAck();

	I2CSendByte(0x0) ;//置WRTC1=0(10H地址)      
	I2CWaitAck();
	IIC_STOP();
}

void I2CWriteDate(unsigned char *BUF)
{		

        WriteTimeOn();

	IIC_START();
	I2CSendByte(0x64); 
        I2CWaitAck();

        I2CSendByte(0x00);//设置写起始地址      
	I2CWaitAck();	
	I2CSendByte(*BUF++);// second     
	I2CWaitAck();	
	I2CSendByte(*BUF++);//minute      
	I2CWaitAck();	
	I2CSendByte(*BUF++);//hour ,二十四小时制     
	I2CWaitAck();	
	I2CSendByte(*BUF++);//week      
	I2CWaitAck();	
	I2CSendByte(*BUF++);//day      
	I2CWaitAck();	
	I2CSendByte(*BUF++);//month      
	I2CWaitAck();	
	I2CSendByte(*BUF);//year      
	I2CWaitAck();	
	IIC_STOP();

	IIC_START();
	I2CSendByte(0x64);      
	I2CWaitAck();   
        I2CSendByte(0x12);//设置写起始地址      
	I2CWaitAck();		
        I2CSendByte(0x00);//清零数字调整寄存器      
	I2CWaitAck();        
	IIC_STOP();  
	
	WriteTimeOff();      
}


//IIC写入8位数据
unsigned char IIC_Write8Bit(unsigned char DAT)
{
  unsigned char num;
  IIC_SDA_DDR(1);
  Delay();
  
  for(num=0x80;num!=0;num>>=1)
  {
    GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
    Delay();
    if((DAT&num)==0)GPIO_ResetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
    else GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
    Delay();
    GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
    Delay();
    
    
  }
  
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  
  //GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  //Delay();
  //GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  //Delay();
  IIC_SDA_DDR(0);
  GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  while((GPIO_ReadInputDataBit(IIC_GPIOx,IIC_SDA_GPIO_Pin)==SET))
  {
    GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
    return 0;
  }
  
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  return 1;
}

unsigned char IIC_Read8BitACK(void)
{
  unsigned char x,IICDATA;
  IIC_SDA_DDR(1);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  IIC_SDA_DDR(0);
  Delay();
  for(x=0x80;x!=0;x>>=1)
  {
    Delay();
    GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
    if(GPIO_ReadInputDataBit(IIC_GPIOx,IIC_SDA_GPIO_Pin))IICDATA|=x;
    else 
    {
      IICDATA&=~x;
    }
    Delay();
    GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  }
  IIC_SDA_DDR(1);
  Delay();
  GPIO_ResetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  return IICDATA;
}

unsigned char IIC_Read8BitNACK(void)
{
  unsigned char x,IICDATA;
  IIC_SDA_DDR(1);
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  IIC_SDA_DDR(0);
  Delay();
  for(x=0x80;x!=0;x>>=1)
  {
    Delay();
    GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
    if(GPIO_ReadInputDataBit(IIC_GPIOx,IIC_SDA_GPIO_Pin))IICDATA|=x;
    else 
    {
      IICDATA&=~x;
     }
    Delay();
    GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  }
  IIC_SDA_DDR(1);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SDA_GPIO_Pin);
  Delay();
  GPIO_SetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  Delay();
  GPIO_ResetBits(IIC_GPIOx,IIC_SCL_GPIO_Pin);
  return IICDATA;
  
}



void SD2405_Read7Byte(unsigned char *BUF)
{
  unsigned char RLEN=0x07;
  IIC_START();
  //IIC_Write8Bit(0x65);
  IIC_Write8Bit(SD2405_READ_ADDRESS);
  //IIC_Write8Bit(0x00);
  while(RLEN>1)
  {
    *BUF++=IIC_Read8BitACK();
    RLEN--;
    
  }
  *BUF=IIC_Read8BitNACK();
  IIC_STOP();
  
}

void SD2405_WriteNByte(unsigned char *BUF,unsigned char ADDR,unsigned char LEN)
{
  unsigned char x;
  
  IIC_START();
  IIC_Write8Bit(0x64);
  IIC_Write8Bit(ADDR);
  for(x=0;x<LEN;x++)
  {
    IIC_Write8Bit(*BUF++);    
    
  }
  IIC_STOP();
}

