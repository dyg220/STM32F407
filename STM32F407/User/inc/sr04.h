#ifndef _SR04_H_
#define _SR04_H_

#include "stm32f4xx.h"                  // Device header
#include "systick.h"

#define TRIG_H		(GPIOB->ODR |= (1<<8))
#define TRIG_L		(GPIOB->ODR &= ~(1<<8))
#define ECHO_Read 	(GPIOB->IDR&(1<<9))

void	HC_SR04_Init(void);
float	HC_SR04_Read_Distance(void);

#endif

