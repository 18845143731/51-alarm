#include"keyProcess.h"
void array2show(ARRAY2SHOW *arrayshow0,uchar wch);	 //函数声明//
void sec2show(SYSTEMTIME *secshow);
SYSTEMTIME showtime;  
extern SYSTEMTIME CurrentTime;
extern ARRAY2SHOW  Alarmandshow;
/****************************************************************************************************
函数名称：key_process(uchar mode)
函数功能：按键处理函数（调节日期，时间，秒表，闹钟）
输入参数：mode		用来选择模式，是修改日期，时间还是闹钟
返回值：无
****************************************************************************************************/
void key_process(uchar mode)
{	
	
	uchar Wch=0;
	uchar flag=0;
	uchar AlarmWch=0;
	uchar HourSecWch=0;
	uchar temp=0;
	switch(mode)		//在最外层循环中检测按键，确定要设置什么
	{
		DS1302_GetTime(&CurrentTime);
		case MODE0:			//设置时间
			showtime=CurrentTime;
			while(1)
			{	 				
				DateToStr(&CurrentTime);
				zifu_dis(1,0,&CurrentTime.DateString[0]); 		//修改时间不影响从1302读日期显示
				//（麻烦的思想）TArray3=show2array3(&CurrentTime.TimeString[0]);	//将显示的字符形式变成可以直接加1的形式
				if(key_scan()==K1||key_scan()==K2||key_scan()==K3||key_scan()==K4)//检测有没有按键按下，有按键按下才执行操作
				{
					switch(key_scan())			//再次检测按键
					{	  
						case K3:				//K3按下，选择时间的哪一位被更改
								 
								Wch++;
								if(Wch==3)
									Wch=0;
								break;						
						case K1:			   //K1按下，数字加一
							   //（麻烦的思想）TArray3[TimeWch]++;			//转化成单个字符形式显示 
								if(Wch==0)
								{
									showtime.Hour++;
									if(showtime.Hour==24)
										showtime.Hour=0;
								}
								else if(Wch==1)
								{
									showtime.Minute++;
									if(showtime.Minute==60)
										showtime.Minute=0;
								}
								else if(Wch==2)
								{
									showtime.Second++;
								 	if(showtime.Second==60)
										showtime.Second=0;
								}
								TimeToStr(&showtime);
								zifu_dis(0,0,&showtime.TimeString[0]); 
								break;
	
						case K2:			   //K2按下，数字减一
								//（麻烦的思想）TArray3[TimeWch]--;
								//（麻烦的思想）zifu_dis(1,0,array32show(TArray3)); 
								if(Wch==0)
								{
									showtime.Hour--;
									if(showtime.Hour==0xff)
										showtime.Hour=0;
								}
								else if(Wch==1)
								{
									showtime.Minute--;
									if(showtime.Minute==0xff)
										showtime.Minute=0;
								}
								else if(Wch==2)
								{
									showtime.Second--;
									if(showtime.Second==0xff)
										showtime.Second=0;
								}
								TimeToStr(&showtime);
								zifu_dis(0,0,&showtime.TimeString[0]); 
								break;
	
						case K4:  			  //K4按下，确定修改，
								flag=1;break;
					 }	 	
			
				}
				 if(flag==1)		 //flag为1时，确定修改，将1302里的时间重置，并退到最初的模式检测
				 {		
					DS1302_SetTime(DS1302_HOUR,showtime.Hour);	
					DS1302_SetTime(DS1302_MINUTE,showtime.Minute);
					DS1302_SetTime(DS1302_SECOND,showtime.Second);
					Wch=0;
					flag=0;
				 	break;
				 } 	
			}
			 break;
		case MODE1:			//设置日期
			showtime=CurrentTime;
			while(1)
			{
				DS1302_GetTime(&CurrentTime);
				TimeToStr(&CurrentTime);
				zifu_dis(0,0,&CurrentTime.TimeString[0]); 		   //修改日期，不影响从1302读时间显示
				//(麻烦的思想)DArray3=show2array3(&CurrentTime.DateString);	   //将显示的字符形式变成可以直接加1的形式
				if(key_scan()==K1||key_scan()==K2||key_scan()==K3||key_scan()==K4)//检测有没有按键按下，有按键按下才执行操作
				{
					switch(key_scan())	//再次检测按键
					{
						case K3:			    //K3按下，选择日期的哪一位被更改
								Wch++;
								if(Wch==3)
									Wch=0;
								break;
						case K1:			   //K1按下，数字加一
							    //（麻烦的思想）DArray3[DateWch]=DArray3[DateWch]+1;
								//（麻烦的思想）zifu_dis(0,0,array32show(DArray3)); 
								if(Wch==0)
									showtime.Year++;
								else if(Wch==1)
								{
									showtime.Month++;
									if(showtime.Month==13)
										showtime.Month=1;
								}		
								else if(Wch==2)
								{
									showtime.Day++;
									if(showtime.Month==1||showtime.Month==3||showtime.Month==5||showtime.Month==7||showtime.Month==8||showtime.Month==10||showtime.Month==12)
										if(showtime.Day==32)
											showtime.Day=0;
									else if(showtime.Month==2)
										if(showtime.Day=30)
											showtime.Day=0;
									else
										if(showtime.Day==31)
											showtime.Day=0;	
								}
								DateToStr(&showtime);
								zifu_dis(1,0,&showtime.DateString[0]); 
								break;
						case K2:			   //K2按下，数字减一
								//（麻烦的思想）DArray3[DateWch]--;
								//（麻烦的思想）zifu_dis(0,0,array32show(DArray3)); 
								if(Wch==0)
									showtime.Year--;
								else if(Wch==1)
									showtime.Month--;
								else if(Wch==2)
									showtime.Day--;
								DateToStr(&showtime);
								zifu_dis(1,0,&showtime.DateString[0]); 
								break;
						case K4: 
											   //K4按下退出此循环，回到模式检测循环
								flag=1;
								break;
					 }
				}
				 if(flag==1)	//flag为1时，确定修改，将1302里的日期重置，并退到最初的模式检测
				 {
				 	DS1302_SetTime(DS1302_YEAR,showtime.Year);	
					DS1302_SetTime(DS1302_MONTH,showtime.Month);
					DS1302_SetTime(DS1302_DAY,showtime.Day);
					flag=0;
					Wch=0;
				 	break;
					
				 }
			}
			 break;
		case MODE2:			//设置闹钟
			while(1)
			{	
				DS1302_GetTime(&CurrentTime);
				DateToStr(&CurrentTime);
				TimeToStr(&CurrentTime);
				zifu_dis(0,0,&CurrentTime.TimeString[0]); 	 //在设置闹钟时不让时间的显示停下
				if(key_scan()==K1||key_scan()==K2||key_scan()==K3||key_scan()==K4)//检测有没有按键按下，有按键按下才执行操作
				{
					switch(key_scan())	//再次检测按键
					{
						case K3:			    //K1按下，选择哪一个闹钟被更改
								AlarmWch++;
								if(AlarmWch==4)
									AlarmWch=0;
								break;
						case K2:			   //K2按下，选择闹钟的小时还是秒被更改
							    HourSecWch++;
								if(HourSecWch==2)
									HourSecWch=0;
								break;							   
						case K1:			   //K3按下，数字加1
								Alarmandshow.Alarm[AlarmWch][HourSecWch]++;
								if(Alarmandshow.Alarm[AlarmWch][HourSecWch]==60)
									Alarmandshow.Alarm[AlarmWch][HourSecWch]=0;
								array2show(&Alarmandshow,AlarmWch);
					
								zifu_dis(2+AlarmWch%2,2+AlarmWch/2*3,&Alarmandshow.showstring[0]);
								break;
						case K4: 			   //K4按下退出此循环，回到模式检测循环
								flag=1;break;
					 }
				}
				 if(flag==1)
				 {
				 	AlarmWch=0;
					HourSecWch=0;		//最好要将AlarmWch,HourSecWch清零，后面要用
				 	flag=0;
				 	break;
					
				 }
			}	
			break;	
		case MODE3:					 //秒表
				
				while(1)	//此层循环用来显示秒表的初始界面	  	
				{
					temp=0;
					showtime.Second=0;
					lcd_init();		
					zifu_dis(0,3,"00.0");
					if(key_scan()==K1)		//K1按下，秒表开始计时
					{
						while(1)	//此层循环是秒表开始后的循环
							{		 
								delay_ms(73);		//再算上程序执行的时间，一共为100ms				 
								sec2show(&showtime);
								zifu_dis(0,3,&showtime.TimeString[0]);	
								if(flag==0)
								showtime.Second++;		//每过100ms，Second++,
								switch(key_scan())
								{
									case K1:
										zifu_dis(temp/3+1,temp*3%9,&showtime.TimeString[0]);			
										temp++;		//读一下秒表，记录下
										if(temp==9)
											temp=0;
										break;
									case K2:
										flag=~flag;
										break;
									case K3:
										flag=2;
										break;
									case K4:
										flag=1;
										break;
								}	
								if(flag==2||flag==1)
								{
									if(flag==2)
										flag=0;
									break;	
								}
							}
					}
					if(flag==1)
					{
						flag=0;
						break;
					}
				}
			lcd_init();
			for(;AlarmWch<4;AlarmWch++)
			{
				//arrayshow.array2[AlarmWch][HourSecWch]=0;
				array2show(&Alarmandshow,AlarmWch);
				zifu_dis(AlarmWch/2+2,AlarmWch%2*3+2,&Alarmandshow.showstring[0]);
			}
			zifu_dis(2,0,"闹钟");
			AlarmWch=0;
			HourSecWch=0;
			break;				
	}
}
 
/***********************************************************************************************
函数名称：array32show(uchar *array3)
函数功能：将存在array[3]里的小时，分钟，秒转换成可以直接显示的形式
输入参数：*array3 		array[3]的首地址
返回值：  show			show[9]的首地址，可以直接用来显示
*************************************************************************************************/
/*uchar *array32show(uchar *array3)
{
	uchar show[5];
	show[0] = *array3/10+0x30 ;
	show[1] = *array3++%10+0x30 ;
	show[2] = ':';
	show[3] = *array3/10+0x30 ;
	show[4] = *array3%10+0x30 ;//用LCD显示，要变成ascii码所以加了0x30，用数码管显示的话就不用加了
	show[5] = '\0';
	return show;	
} *///没有用到

/***********************************************************************************************
函数名称：show2array3(uchar *show)
函数功能：将存在show[]里的可直接显示的字符转换成可以直接加一的array[3]
输入参数：*show 		show数组的首地址
返回值：  array3		array数组的首地址，可以直接用来做加一操作
*************************************************************************************************/
/*uchar *show2array3(uchar *show)
{
	uchar array3[3];
	array3[0]=(show[0]-0x30)*10+(show[1]-0x30);
	array3[1]=(show[3]-0x30)*10+(show[4]-0x30);		
	array3[2]=(show[6]-0x30)*10+(show[7]-0x30);
	return array3;	
}*/ 

void array2show(ARRAY2SHOW *arrayshow0,uchar wch)
{
	arrayshow0->showstring[0] = arrayshow0->Alarm[wch][0]/10+0x30 ;
	arrayshow0->showstring[1] = arrayshow0->Alarm[wch][0]%10+0x30 ;
	arrayshow0->showstring[2] =':';
	arrayshow0->showstring[3] = arrayshow0->Alarm[wch][1]/10+0x30 ;
	arrayshow0->showstring[4] = arrayshow0->Alarm[wch][1]%10+0x30 ;
	//用LCD显示，要变成ascii码所以加了0x30，用数码管显示的话就不用加了
	arrayshow0->showstring[5] = '\0';
}

void sec2show(SYSTEMTIME *secshow)
{
	secshow->TimeString[0]=secshow->Second/100+0x30;
	secshow->TimeString[1]=secshow->Second%100/10+0x30;
	secshow->TimeString[2]='.';
	secshow->TimeString[3]=secshow->Second%10+0x30;
	secshow->TimeString[4]='\0';
}
