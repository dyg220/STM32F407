#ifndef _USART1_H_
#define _USART1_H_
#include "stm32f4xx.h"        

void USART1_Init(u32 baud);
u8 USART1_RecvByte(void);
void USART1_SendByte(u8 Byte);


#endif // !_USART1_H_

