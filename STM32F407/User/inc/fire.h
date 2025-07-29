#ifndef _FIRE_H_
#define _FIRE_H_
#include "stm32f4xx.h"                  // Device header


//检测到火焰时为低电平
#define Fire_DETECT (GPIOA->IDR&(0x01<<4)==0 ? 1:0)

void Fire_Init(void);

#endif

