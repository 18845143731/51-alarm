#ifndef __BUZZER_H
#define _BUZZER_H

#include<reg52.h>
#include"delay.h"

#ifndef uchar
	#define uchar 	unsigned char
#endif

sbit BuzzerPort=P2^2;

void buzzer_on(void);
void buzzer_off(void);
void buzzer_delay(void);

#endif
