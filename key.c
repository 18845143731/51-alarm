/*************************************************************************************************
程序说明：按键的检测程序（基于51单片机），现在只有独立按键检测函数
Author:	xingcheng
IO说明：按键接的
**************************************************************************************************/

#include"key.h"
sbit KeyPort2=P1^5;
sbit KeyPort0=P1^7;						
sbit KeyPort1=P1^6;
sbit KeyPort3=P1^4;	//自己焊的按键接的单片机引脚
//sbit KeyPort2=P1^2;
//sbit KeyPort0=P1^0;						
//sbit KeyPort1=P1^1;
//sbit KeyPort3=P1^3;

/************************************************************************
函数名称：key_scan()
函数功能：4个独立按键检测
输入参数：无
返回值：KeyV		通过返回值的不同来确定哪个按键被按下
*************************************************************************/ 
uchar key_scan()
{
	uchar KeyV;
	KEYPORT=0xff;		//从51IO口读数据，一般要先给锁存器写1，
						//具体请参考51IO口内部结构						
	if(KeyPort0==0||KeyPort1==0||KeyPort2==0||KeyPort3==0)		//判断是否有按键按下
	//这里改成if((P3&0xf0)!=0xf0）总是错，原因可能是P3读数据不是从引脚读的
	//而是从锁存器读的，一直是0xff
	{
		delay_ms(10);		//防止抖动(拿板子实验时，发现这里延不延时并无影响)
		 if(KeyPort0==0)		//判断哪个按键被按下//
		{	
			KeyV=K1;
		}
		else if(KeyPort1==0)
		{
			KeyV= K2;
		}
		else if(KeyPort2==0)
		{	
			KeyV=K3;
		}
		else if(KeyPort3==0)
		{
			KeyV=K4;
		}
		else 
		{
			KeyV= 0;
		}		  			//判断哪个按键被按下//
		
		if(KeyV != 0)		//有按键按下时，进行松手检测
              while(KeyPort0==0||KeyPort1==0||KeyPort2==0||KeyPort3==0);
		delay_ms(10);		//延时消抖（拿板子实验，这里延时非常必要）
   }

    return KeyV;			//返回KeyV来标识哪一个按键被按下
}

/*****************************有时间再完善连按，长按等功能************************/

/*		while((KEYPORT&0Xf0)!=NO_KEY)
		{
			delay_ms(15);
			PressCnt--;
			if(PressCnt==0)
				{
					PressCnt=SHORTCNT;
					return KeyV;
				}
		}
	}
	delay_ms(15);
	if((KEYPORT&0Xf0)==NO_KEY)
	{
		ReleaseCon=0;
		return KeyV;
	}
  */
