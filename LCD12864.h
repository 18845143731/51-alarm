/**************dis_12864.h***************/
#ifndef __LCD12864_H__
#define __LCD12864_H__

#include"delay.h"
 #include <reg52.h>
#define uchar unsigned char
 #define uint  unsigned int
 
/*12864端口定义*/
 #define LCD_data  P0             //数据口
 sbit LCD_RS  =  P2^3;            //寄存器选择输入 
 sbit LCD_RW  =  P2^4;            //液晶读/写控制
 sbit LCD_EN  =  P2^5;            //液晶使能控制
 
sbit LCD_PSB =  P3^3;            //串/并方式控制
 


/*函数声明*/
 void delay(int ms);
 void lcd_init(); 
 void beep();
 void  dataconv();
 void lcd_pos(uchar X,uchar Y);  //确定显示位置
 void zifu_dis (uchar X,uchar Y,uchar *dis);
 
#endif
