/**************************************************************************
  
                   		THE REAL TIMER DS1302 DRIVER LIB
  
             		COPYRIGHT (c)   2005 BY JJJ.
                       		--  ALL RIGHTS RESERVED  --
  
   File Name:       DS1302.h
   Author:          Jiang Jian Jun
   Created:         2003/7/21
   Modified:		NO
   Revision: 		1.0
   re
***************************************************************************/
#include"ds1302.h"

/***************************************************************************
函数名称：DS1302InputByte(unsigned char d)
函数功能：实时时钟写入一个字节（内部函数）
输入参数：d			要写入的数据
返回值：无
***************************************************************************/
void DS1302InputByte(unsigned char d) 	
{ 
    unsigned char i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        DS1302_IO = ACC0;           	//相当于汇编中的 RRC
        DS1302_CLK = 1;
        DS1302_CLK = 0;
        ACC = ACC >> 1; 
    } 
}

/***************************************************************************
函数名称：DS1302OutputByte(void)
函数功能：实时时钟读取一个字节（内部函数）
输入参数：无
返回值：ACC			读到的数据
***************************************************************************/
unsigned char DS1302OutputByte(void) 	
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//相当于汇编中的 RRC
        ACC7 = DS1302_IO;
        DS1302_CLK = 1;
        DS1302_CLK = 0;
    } 
    return(ACC); 
}

/***************************************************************************
函数名称：Write1302(unsigned char ucAddr, unsigned char ucDa)	
函数功能：往实时时钟指定地址写数据
输入参数：ucAddr		要写数据的地址
		  ucDa			要写入的数据
返回值：无
***************************************************************************/
void Write1302(unsigned char ucAddr, unsigned char ucDa)	
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr);       	// 地址，命令
    DS1302InputByte(ucDa);       	// 写1Byte数据
//    DS1302_CLK = 1;
    DS1302_RST = 0;
} 

/***************************************************************************
函数名称：Read1302(unsigned char ucAddr)	
函数功能：读取ds1302某地址的数据
输入参数：ucAddr		要读数据的地址
返回值：  ucData		读出的数据
***************************************************************************/
unsigned char Read1302(unsigned char ucAddr)	//读取ds1302某地址的数据
{
    unsigned char ucData;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr|0x01);        // 地址，命令 
    ucData = DS1302OutputByte();         // 读1Byte数据
//    DS1302_CLK = 1;
    DS1302_RST = 0;
    return(ucData);
}

/***************************************************************************
函数名称：DS1302_SetProtect(bit flag)        
函数功能：是否写保护
输入参数：flag		
返回值：  无 
其他：flag为1时,0x8E对应的control register最高位为1，写保护开启
***************************************************************************/
void DS1302_SetProtect(bit flag)        //是否写保护
{
	if(flag)
		Write1302(0x8E,0x80);
	else
		Write1302(0x8E,0x00);
}

/***************************************************************************
函数名称：DS1302_SetTime(unsigned char Address, unsigned char Value)        
函数功能：向指定寄存器写时间
输入参数：Address		寄存器地址
		  Value			要写入的时间（hex码）
返回值：  无 
其他：可以先用宏定义定义好year，month，hour等的地址
***************************************************************************/
void DS1302_SetTime(unsigned char Address, unsigned char Value)        // 设置时间函数
{
	DS1302_SetProtect(0);
	Write1302(Address, ((Value/10)<<4 | (Value%10))); 		//将hex码转化为BCD码
}

/***************************************************************************
函数名称：DS1302_GetTime(SYSTEMTIME *Time)
函数功能：读出日期和时间，将它们存入Time这个结构体中
输入参数：*Time		要存日期和时间的结构体的地址
返回值：  无 
***************************************************************************/
void DS1302_GetTime(SYSTEMTIME *Time)
{
	unsigned char ReadValue;
	ReadValue = Read1302(DS1302_SECOND);
	Time->Second = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	//八进制转为十进制
	ReadValue = Read1302(DS1302_MINUTE);
	Time->Minute = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_HOUR);
	Time->Hour = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_DAY);
	Time->Day = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
	ReadValue = Read1302(DS1302_WEEK);
	Time->Week = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_MONTH);
	Time->Month = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_YEAR);
	Time->Year = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
}

/***************************************************************************
函数名称：DateToStr(SYSTEMTIME *Time)	 
函数功能：将读出的日期变成便于显示的字符形式
输入参数：*Time		要存字符的结构体
返回值：无 
***************************************************************************/
void DateToStr(SYSTEMTIME *Time)	 
{
	Time->DateString[0] = Time->Year/10+0x30 ;	 //·分离个位和十位
	Time->DateString[1] = Time->Year%10+0x30 ;
	Time->DateString[2] = '-';
	Time->DateString[3] = Time->Month/10+0x30;
	Time->DateString[4] = Time->Month%10+0x30 ;
	Time->DateString[5] = '-';
	Time->DateString[6] = Time->Day/10+0x30 ;
	Time->DateString[7] = Time->Day%10+0x30 ;  //用LCD显示，要变成ascii码所以加了0x30，用数码管显示的话就不用加了
	Time->DateString[8] = '\0';
}

/***************************************************************************
函数名称：TimeToStr(SYSTEMTIME *Time)
函数功能：将读出的时间变成便于显示的字符形式
输入参数：*Time		要存字符的结构体
返回值：无 
***************************************************************************/
void TimeToStr(SYSTEMTIME *Time)
{
	Time->TimeString[0] = Time->Hour/10+0x30 ;
	Time->TimeString[1] = Time->Hour%10+0x30 ;
	Time->TimeString[2] = ':';
	Time->TimeString[3] = Time->Minute/10+0x30 ;
	Time->TimeString[4] = Time->Minute%10+0x30 ;
	Time->TimeString[5] = ':';
	Time->TimeString[6] = Time->Second/10+0x30;
	Time->TimeString[7] = Time->Second%10+0x30 ;//用LCD显示，要变成ascii码所以加了0x30，用数码管显示的话就不用加了
	Time->DateString[8] = '\0';
}

/***************************************************************************
函数名称：Initial_DS1302(void)
函数功能：初始化ds1302
输入参数：无
返回值：无 
***************************************************************************/
void Initial_DS1302(void)
{
	unsigned char Second=Read1302(DS1302_SECOND);
	if(Second&0x80)		  
		DS1302_SetTime(DS1302_SECOND,0);
}
				   
/********************************************************************************
void BurstWrite1302(unsigned char *pWClock)	//往ds1302写入时钟数据（多字节方式）
{
    unsigned char i;
    Write1302(0x8e,0x00);         	// 控制命令,WP=0,写操作
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(0xbe);        	// 0xbe:时钟多字节写命令
    for (i = 8; i>0; i--)     		//8Byte = 7Byte 时钟数据 + 1Byte 控制
    {
        DS1302InputByte(*pWClock); 	// 写1Byte数据
        pWClock++;
    }
    DS1302_CLK = 1;
    DS1302_RST = 0;
} 

void BurstRead1302(unsigned char *pRClock)	//读取ds1302时钟数据（时钟多字节方式）
{
    unsigned char i;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(0xbf);             	// 0xbf:时钟多字节读命令 
    for (i=8; i>0; i--) 
    {
       *pRClock = DS1302OutputByte();   // 读1Byte数据 
       pRClock++;
    }
    DS1302_CLK = 1;
    DS1302_RST = 0;
}

void DS1302_TimeStop(bit flag)           // 是否将时钟停止
{
	unsigned char Data;
	Data=Read1302(DS1302_SECOND);
	DS1302_SetProtect(0);
	if(flag)
		Write1302(DS1302_SECOND, Data|0x80);
	else
		Write1302(DS1302_SECOND, Data&0x7F);
}
********************************************************************************/
