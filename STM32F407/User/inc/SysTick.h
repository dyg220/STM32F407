#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
#include "led.h"

void delay_us(u32 xus);
void delay_ms(u16 xms);
void delay_xms(u32 xms);
void SysTick_Config_Own(u8 xms);
void Sys_Interrupt_delay(u32 xms);

#endif

