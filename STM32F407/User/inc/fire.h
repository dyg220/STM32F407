#ifndef _FIRE_H_
#define _FIRE_H_
#include "stm32f4xx.h"                  // Device header


//��⵽����ʱΪ�͵�ƽ
#define Fire_YES	!(GPIOA->IDR&(0x01<<4))
#define Fire_NO		(GPIOA->IDR&(0x01<<4))
void Fire_Init(void);

#endif

