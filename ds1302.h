#ifndef _DS1302_H
#define _DS1302_H

#include<reg52.h>
#include"delay.h"
#include<intrins.h>

#ifndef	uchar
	#define uchar unsigned char
#endif
sbit  DS1302_CLK = P3^6;            //实时时钟时钟线引脚
sbit  DS1302_IO  = P3^5;              //实时时钟数据线引脚
sbit  DS1302_RST = P3^4;              //实时时钟复位线引脚
//sbit  DS1302_CLK = P3^6;            //实时时钟时钟线引脚
//sbit  DS1302_IO  = P3^4;              //实时时钟数据线引脚
//sbit  DS1302_RST = P3^5;              //实时时钟复位线引脚

sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;


typedef struct __SYSTEMTIME__
{
	unsigned int Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned char Week;
	unsigned char Day;
	unsigned char Month;
	unsigned char  Year;
	unsigned char DateString[9];
	unsigned char TimeString[9];

}SYSTEMTIME;	//定义的时间类型

#define AM(X)	X
#define PM(X)	(X+12)                   	  // 转成24小时制
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_RAM(X)	(0xC0+(X)*2)   	//用于计算ds1302RAM地址的宏

void DS1302InputByte(unsigned char d) ;
unsigned char DS1302OutputByte(void)  ;
void Write1302(unsigned char ucAddr, unsigned char ucDa);
void DS1302_SetProtect(bit flag);
unsigned char Read1302(unsigned char ucAddr);
void DS1302_SetTime(unsigned char Address, unsigned char Value);
void DS1302_GetTime(SYSTEMTIME *Time);
void DateToStr(SYSTEMTIME *Time);
void TimeToStr(SYSTEMTIME *Time);
void Initial_DS1302(void);
#endif
