#ifndef _KEY_H_
#define _KEY_H_
#include "stm32f4xx.h"                  // Device header

#define KEY1_PRESS	(GPIOA->IDR&(0x01<<0))
#define KEY2_PRESS	!GPIOE->IDR&(0x01<<2))
#define KEY3_PRESS	!(GPIOE->IDR&(0x01<<3))
#define KEY4_PRESS	!(GPIOE->IDR&(0x01<<4))

void Key_Init(void);  //°´¼ü³õÊ¼»¯
u8 Key_Scan(void);

#endif

