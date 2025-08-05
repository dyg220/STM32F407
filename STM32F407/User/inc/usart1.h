#ifndef _USART1_H_
#define _USART1_H_
#include "stm32f4xx.h"        
#define Max_Size 256

typedef struct {
	char data[Max_Size];
	u16 index;
	u8 flag;
}USART_INFO;


void USART1_Init(u32 baud);
u8   USART1_RecvByte(void);
void USART1_SendByte(u8 Byte);
void USART1_SendStr(char* str);
void USART1_RecvStr(char* str);



#endif // !_USART1_H_

