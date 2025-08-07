#ifndef _FIRE_H_
#define _FIRE_H_

#include "stm32f4xx.h"                  // Device header

#define Fire_Yes	(GPIOA->IDR&(1<<4))


void Fire_Init(void);

#endif

