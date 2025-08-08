#ifndef _IWDG_H_
#define _IWDG_H_

#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "systick.h"

void IWDG_Init(void);
void IWDG_Feed(void);



#endif