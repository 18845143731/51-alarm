#ifndef __DELAY_H
#define __DELAY_H

#include<reg52.h>

#define freCrystal 12000000UL 			//外接晶振频率频率

typedef unsigned int u16;

void delay_10us(int us);
void delay_ms(int num_ms);

#endif
