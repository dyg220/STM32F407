#include "usart2.h"
#include <stdio.h>

void USART2_Init(u32 baud)
{
	/*配置IO口*/
	//I0口时钟使能
	RCC->AHB1ENR = (1 << 0);
	//USART1的时钟使能
	RCC->APB1ENR |= (1 << 17);

	//配置复用模式
	GPIOA->MODER &= ~((3 << 4) | (3 << 6));
	GPIOA->MODER |= ((2 << 4) | (2 << 6));
	//不开上下拉
	GPIOA->PUPDR &= ~((3 << 4) | (3 << 6));
	//复用推挽
	GPIOA->OTYPER &= ~((1 << 2 | (1 << 3)));
	//输出速度
	GPIOA->OSPEEDR &= ~((3 << 4) | (3 << 6));
	//复用USART
	GPIOA->AFR[0] &= ~((0xf << 8) | (0xf << 12));
	GPIOA->AFR[0] |= ((7 << 8) | (7 << 12));

	/*配置USART1*/
	//配置波特率(BRR)
	USART2->BRR = 42000000 / baud;
	//CR1
	USART2->CR1 &= ~(1 << 15);//16倍过采样
	USART2->CR1 &= ~(1 << 12);//8位字长
	USART2->CR1 &= ~(1 << 10);//奇校验位(关闭)
	USART2->CR1 |= (1 << 3);//发送器使能
	USART2->CR1 |= (1 << 2);//接收器使能
	//CR2
	USART2->CR2 &= ~(3 << 12);//停止位（1位）


	/*NVIC配置*/
	//设置具体中断通道优先级
	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
	//使能中断通道
	NVIC_EnableIRQ(USART2_IRQn);

	//使能接收中断+空闲中断控制位
	USART2->CR1 |= (1 << 5);
	USART2->CR1 |= (1 << 4);

	//USART使能
	USART2->CR1 |= (1 << 13);

}

//接收一个字节数据
u8 USART2_RecvByte(void)
{
	u8 data = 0;
	//等待接受数据寄存器不为空
	while ((USART2->SR&(1 << 5)) == 0);
	//从DR中读出数据
	data = USART2->DR;
	return data;
}

//发送一个字节数据
void USART2_SendByte(u8 Byte)
{
	//等待发送数据寄存器为空
	while ((USART2->SR&(1 << 7)) == 0);
	//把数据发给DR
	USART2->DR = Byte;
}


void USART2_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART2_SendByte(*str);
		str++;
	}
	USART2_SendByte('\0');
}

void USART2_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART2_RecvByte();
		*str = data;
		str++;
	} while (data != '\n');
	str--;			//接收到\n
	*str = '\0';	//将\n覆盖
}


USART_INFO USART2_Recv = { 0 };

void USART2_IRQHandler(void)
{
	u8 clean = 0;
	//接受中断
	if (USART2->SR&(1 << 5))
	{
		//清除标志位
		USART2_Recv.data[USART2_Recv.index] = USART2->DR;	//即接受数据又能清除标志位
		USART2_Recv.index++;
	}
	//空闲中断
	else if (USART2->SR&(1 << 4))
	{
		//清除标志位
		clean = USART2->SR;
		clean = USART2->DR;
		(void)clean;		//去除警告
		USART2_Recv.flag = 1;
		USART2_Recv.data[USART2_Recv.index] = '\0';
		USART2_Recv.index = 0;	//下标清零
	}

}
