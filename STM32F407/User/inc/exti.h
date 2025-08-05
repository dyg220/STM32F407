#ifndef _EXTI_H_
#define _EXTI_H_

#include "stm32f4xx.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "beep.h"

void EXTI0_IRQ_Config(void);
void EXTI4_IRQ_Config(void);
void EXTI6_SoftIRQ_Config(void);

#endif


