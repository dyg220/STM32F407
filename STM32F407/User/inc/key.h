#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "systick.h"

#define Key1Press	(GPIOA->IDR&(1<<0))
#define Key2Press	!(GPIOE->IDR&(1<<2))
#define Key3Press	!(GPIOE->IDR&(1<<3))
#define Key4Press	!(GPIOE->IDR&(1<<4))


void Key_Init(void);
u8 Key_Scan(void);

#endif

