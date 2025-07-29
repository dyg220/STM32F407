#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx.h"                  // Device header

#define LED1_ON 	(GPIOC->ODR &= ~(1 << 4))
#define LED2_ON 	(GPIOC->ODR &= ~(1 << 5))
#define LED3_ON 	(GPIOC->ODR &= ~(1 << 6))
#define LED4_ON 	(GPIOC->ODR &= ~(1 << 7))

#define LED1_OFF 	(GPIOC->ODR |= 1 << 4)
#define LED2_OFF 	(GPIOC->ODR |= 1 << 5)
#define LED3_OFF 	(GPIOC->ODR |= 1 << 6)
#define LED4_OFF 	(GPIOC->ODR |= 1 << 7)


void LED_Init(void);
void LED_ALLOFF(void);
void LED_ALLON(void);
void LED_ON(u8 num);
void LED_OFF(u8 num);

#endif

