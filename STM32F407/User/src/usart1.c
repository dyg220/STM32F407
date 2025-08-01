#include "usart1.h"

//PA9--TX
//PA10--RX
void USART1_Init(u32 baud)
{
	/*配置IO口*/
	//I0口时钟使能
	RCC->AHB1ENR = (1 << 0);
	//USART1的时钟使能
	RCC->APB2ENR |= (1 << 4);

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


	/*配置USART1*/
	//配置波特率(BRR)
	USART1->BRR = 84000000 / baud;
	//CR1
	USART1->CR1 &= ~(1 << 15);//16倍过采样
	USART1->CR1 &= ~(1 << 12);//8位字长
	USART1->CR1 &= ~(1 << 10);//奇校验位(关闭)
	USART1->CR1 |= (1 << 3);//发送器使能
	USART1->CR1 |= (1 << 2);//接收器使能
	//CR2
	USART1->CR2 &= ~(3 << 12);//停止位（1位）
	//USART使能
	USART1->CR1 |= (1 << 13);

}

//接收一个字节数据
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//等待接受数据寄存器不为空
	while ((USART1->SR&(1 << 5)) == 0);
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

void USART1_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART1_SendByte(*str);
		str++;
	}
	USART1_SendByte('\0');
}

void USART1_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART1_RecvByte();
		*str = data;
		str++;
	} while (data != '\n');
	str--;			//接收到\n
	*str = '\0';	//将\n覆盖
}