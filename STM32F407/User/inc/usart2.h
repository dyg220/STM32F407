#ifndef _USART2_H_
#define _USART2_H_

#include "stm32f4xx.h"                  // Device header
#include "usart1.h"

void USART2_Init(u32 Baud);
void USART2_SendByte(u8 Byte);
u8 USART2_RecvByte(void);

void USART2_SendStr(char* str);
void USART2_RecvStr(char* str);


#endif

