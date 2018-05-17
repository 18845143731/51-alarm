/***********************************************************************************
程序说明：利用12864液晶和ds1302配合按键实现 万年历，四路可调闹钟，秒表(基于51单片机)
作者：哈尔滨工程大学  黄上城
***********************************************************************************/
#include <reg52.h>
#include<stdio.h>
#include"delay.h"
#include"ds1302.h"
#include"LCD12864.h"
#include"key.h"
#include"buzzer.h"
#include"keyProcess.h"
SYSTEMTIME  CurrentTime;	//存储当前从ds1302中读到的时间日期等
ARRAY2SHOW  Alarmandshow;	//存储闹钟的时间，和用于闹钟显示的字符串
char code table[7][20]={{"星期壹"},{"星期贰"},{"星期叁"},{"星期肆"},{"星期伍"},{"星期陆"},{"星期日"}};
sbit led=P1^7;
void main()
{	
	uchar mode;
	Initial_DS1302();				//ds1302初始化
//	DS1302_SetTime(DS1302_HOUR,10);	
//	DS1302_SetTime(DS1302_MINUTE,0);
//	DS1302_SetTime(DS1302_SECOND,0);//向ds1302中写初始时间
//	DS1302_SetTime(DS1302_YEAR,17);	
//	DS1302_SetTime(DS1302_MONTH,1);
//	DS1302_SetTime(DS1302_DAY,16);	//向ds1302中写初始日期
	DS1302_SetTime(DS1302_WEEK,3);
	
	lcd_init();						//lcd12864初始化
	zifu_dis(2,0,"闹钟");
	zifu_dis(2,2,"00:00");
	zifu_dis(2,5,"00:00");
	zifu_dis(3,2,"00:00");
	zifu_dis(3,5,"00:00");			 //设置闹钟的初始显示
  	
	while(1)
	{
		if(key_scan()==K1||key_scan()==K2||key_scan()==K3||key_scan()==K4)
		{				
			switch (key_scan())
			{	
				case K1: mode=MODE0;break;		//MODE0设置时间
				case K2: mode=MODE1;break;		//MODE0设置日期
				case K3: mode=MODE2;break;		//MODE0设置闹钟
				case K4: mode=MODE3;break;		//MODE0设置秒表
			}
			key_process(mode);				   //按键处理函数
		}		
		DS1302_GetTime(&CurrentTime);
		DateToStr(&CurrentTime);
		TimeToStr(&CurrentTime);
		zifu_dis(0,0,&CurrentTime.TimeString[0]); 
		zifu_dis(1,0,&CurrentTime.DateString[0]); 		 //读出ds1302里的时间，在lcd上显示
		zifu_dis(1,4,table[CurrentTime.Week]);
		
		if((CurrentTime.Hour==Alarmandshow.Alarm[0][0]&&CurrentTime.Minute==Alarmandshow.Alarm[0][1])||
		   (CurrentTime.Hour==Alarmandshow.Alarm[1][0]&&CurrentTime.Minute==Alarmandshow.Alarm[1][1])||
		   (CurrentTime.Hour==Alarmandshow.Alarm[2][0]&&CurrentTime.Minute==Alarmandshow.Alarm[2][1])||
		   (CurrentTime.Hour==Alarmandshow.Alarm[3][0]&&CurrentTime.Minute==Alarmandshow.Alarm[3][1]))
		   //检查所设的闹钟时间和现在的时间是否一致，是则响蜂鸣器。
		   
				buzzer_delay();
	}		
}
												
