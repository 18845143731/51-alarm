#include<reg52.h>
#include"delay.h"
/****************************************************
函数名称：	delay_us
函数功能:		延时 us（12M晶振时范围为1us到65536us）
输入：			num_us
输出：			无
！！！程序有小问题//
****************************************************/

/****************************************************
函数名称：	delay_ms
函数功能:		延时 ms（12M晶振时范围为1us到65536us）
输入：			num_ms
输出：			无
****************************************************/
void delay_ms(int num_ms)
{
	int i;
	do
	{
		i=freCrystal/96000;
		while(--i);				//96T per loop
	}while(--num_ms);
	

}
void delay_10us(unsigned char us)
{
	while(us--);

}	
