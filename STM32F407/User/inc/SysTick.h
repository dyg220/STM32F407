#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "stm32f4xx.h"    


void systick_us(u32 xus);
void systick_ms(u32 xms);
void systick_xms(u32 xms);
void systick_interrupt(u32 xms);
void SysTick_Config_Own(u8 xms);
#endif