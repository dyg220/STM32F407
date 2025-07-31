#include "usart1.h"

//PA9--TX
//PA10--RX
void USART1_Init(u32 baud)
{
	/*配置IO口*/
	//I0口时钟使能
	RCC->AHB1ENR = (1 << 0);
	//配置复用模式
	GPIOA->MODER &= ~((3 << 18) | (3 << 20));
	GPIOA->MODER |= ((2 << 18) | (2 << 20));
	//不开上下拉
	GPIOA->PUPDR &= ~((3 << 18) | (3 << 20));
	//复用推挽
	GPIOA->OTYPER &= ~((1 << 9) | (1 << 10));
	//输出速度
	GPIOA->OSPEEDR &= ~((3 << 18) | (3 << 20));
	//复用USART
	GPIOA->AFR[1] &= ~((0xf << 4) | (0xf << 8));
	GPIOA->AFR[1] |= ((7 << 4) | (7 << 8));


}

//接收一个字节数据
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//等待接受数据寄存器不为空
	while ((USART1->SR &(1 << 5)) == 0);
	//从DR中读出数据
	data = USART1->DR;
	return data;
}

//发送一个字节数据
void USART1_SendByte(u8 Byte)
{
	//等待发送数据寄存器为空
	while ((USART1->SR&(1 << 7)) == 0);
	//把数据发给DR
	USART1->DR = Byte;
}