#include "usart2.h"

/*********************************************************
*函 数 名：USART2_Init
*函数功能：USART2初始化
*参    数：None
*返 回 值：None
*备    注：USART2_TX---PA2  USART2_RX---PA3
**********************************************************/
void USART2_Init(u32 Baud)
{
	/*配置IO口*/
	//IO口时钟使能
	RCC->AHB1ENR |= (1 << 0);
	//USART2的时钟使能
	RCC->APB1ENR |= (1 << 17);
	//配置复用模式
	GPIOA->MODER &= ~((3 << 4) | (3 << 6));
	GPIOA->MODER |= ((2 << 4) | (2 << 6));
	//不开上下拉
	GPIOA->PUPDR &= ~((3 << 4) | (3 << 6));
	//复用推挽
	GPIOA->OTYPER &= ~((1 << 2) | (1 << 3));
	//输出速度
	GPIOA->OSPEEDR &= ~((3 << 4) | (3 << 6));
	//复用USART
	GPIOA->AFR[0] &= ~((0xf << 8) | (0xf << 12));
	GPIOA->AFR[0] |= ((7 << 8) | (7 << 12));

	/*配置USART2*/
	//配置波特率(BRR)
	USART2->BRR = 42000000 / Baud;
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

/*********************************************************
*函 数 名：USART2_SendByte
*函数功能：发送一个字节数据
*参    数：u8 Byte
*返 回 值：None
*备    注：
**********************************************************/
void USART2_SendByte(u8 Byte)
{
	//等待发送数据寄存器为空
	while ((USART2->SR & (1 << 7)) == 0);
	//把数据发给DR
	USART2->DR = Byte;
}

/*********************************************************
*函 数 名：USART2_RecvByte
*函数功能：接收一个字节数据
*参    数：None
*返 回 值：u8   收到的数据
*备    注：
**********************************************************/
u8 USART2_RecvByte(void)
{
	u8 data = 0;
	//等待接受数据寄存器不为空
	while ((USART2->SR & (1 << 5)) == 0);
	//从DR中读出数据    
	data = USART2->DR;
	return data;
}


/*********************************************************
*函 数 名：USART2_SendStr
*函数功能：发送一个字符串数据
*参    数：u8* str
*返 回 值：None
*备    注：
**********************************************************/
void USART2_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART2_SendByte(*str);//发送一个字节数据   //abc\0
		str++;//指针偏移
	}
	USART2_SendByte('\0');
}

/*********************************************************
*函 数 名：USART2_RecvStr
*函数功能：接收一个字符串数据
*参    数：u8* str
*返 回 值：None
*备    注：
**********************************************************/
void USART2_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART2_RecvByte();//发送一个字节数据   //abc\n
		*str = data;
		str++;
	} while (data != '\n');
	str--;
	*str = '\0';
}


USART_INFO USART2_Recv = { 0 };
void USART2_IRQHandler(void)
{
	u8 clean = 0;
	//接受中断
	if (USART2->SR&(1 << 5))
	{
		//清除标志位
		if (USART2_Recv.index < Max_Size - 1)
		{
			USART2_Recv.data[USART2_Recv.index] = USART2->DR;//即接受数据又能清除标志位
			USART2_Recv.index++;
		}
	}
	//空闲中断
	else if (USART2->SR&(1 << 4))
	{
		//清除标志位
		clean = USART2->SR;
		clean = USART2->DR;
		(void)clean;//去除警告
		USART2_Recv.flag = 1;
		USART2_Recv.data[USART2_Recv.index] = '\0';
		USART2_Recv.index = 0;//下标清零
	}

}






