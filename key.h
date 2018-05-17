#ifndef __KEY_H
#define _KEY_H

#include<reg52.h>
#include"delay.h"

#ifndef uchar
	#define uchar 	unsigned char
#endif

#define KEYPORT P3		//	  四个按键接在了P3口的四个引脚
#define NO_KEY 		0xf0
#define K1	 		0X01
#define K2	 		0X02
#define K3		 	0X03
#define K4			0X04
#define KEYSUB	 		0X02
#define KEYADD	 		0X01
#define KEYSET		 	0X04
#define KEYNEXT			0X03	//K1，2,3,4，和这些是一样的，只是写.c文件时好读
#define LONGCNT 	150
#define SHORTCNT	12



			   
uchar key_scan();

#endif
