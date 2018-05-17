#ifndef __KEYPROCESS_H
#define _KEYPROCESS_H

#include<reg52.h>
#include<stdio.h>
#include"delay.h"
#include"key.h"
#include"ds1302.h"
#include"LCD12864.h"


#ifndef uchar
	#define uchar 	unsigned char
#endif

typedef struct _ARRAYSHOW_
{
	unsigned char   showstring[6];
	unsigned char  Alarm[4][2];
}ARRAY2SHOW;

typedef struct _SHOW_
{
	unsigned char   showstring[6];
	unsigned char  array2[4][2];
}show;

#define MODE0 		0X00
#define MODE1		0X01
#define MODE2 		0X02
#define MODE3		0X03
#define TIMESET		MODE0	
#define DATESET		MODE1
#define ALARMSET	MODE2
#define SECCON		MODE3

void key_process(uchar mode);

#endif
