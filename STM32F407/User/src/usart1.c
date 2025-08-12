#include "usart1.h"

/*********************************************************
*函 数 名：USART1_Init
*函数功能：USART1初始化
*参    数：None
*返 回 值：None
*备    注：USART1_TX---PA9  USART1_RX---PA10
**********************************************************/
void USART1_Init(u32 Baud)
{
	/*配置IO口*/
	//IO口时钟使能
	RCC->AHB1ENR |= (1 << 0);
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
	USART1->BRR = 84000000 / Baud;
	//CR1
	USART1->CR1 &= ~(1 << 15);//16倍过采样
	USART1->CR1 &= ~(1 << 12);//8位字长
	USART1->CR1 &= ~(1 << 10);//奇校验位(关闭)
	USART1->CR1 |= (1 << 3);//发送器使能
	USART1->CR1 |= (1 << 2);//接收器使能
	//CR2
	USART1->CR2 &= ~(3 << 12);//停止位（1位）

	/*NVIC配置*/
	//设置具体中断通道优先级
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(7 - 2, 2, 2));
	//使能中断通道
	NVIC_EnableIRQ(USART1_IRQn);

	//使能接收中断+空闲中断控制位
	USART1->CR1 |= (1 << 5);
	USART1->CR1 |= (1 << 4);

	//USART使能
	USART1->CR1 |= (1 << 13);

}


/*********************************************************
*函 数 名：USART1_SendByte
*函数功能：发送一个字节数据
*参    数：u8 Byte
*返 回 值：None
*备    注：
**********************************************************/
void USART1_SendByte(u8 Byte)
{
	//等待发送数据寄存器为空
	while ((USART1->SR & (1 << 7)) == 0);
	//把数据发给DR
	USART1->DR = Byte;
}

/*********************************************************
*函 数 名：USART1_RecvByte
*函数功能：接收一个字节数据
*参    数：None
*返 回 值：u8   收到的数据
*备    注：
**********************************************************/
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//等待接受数据寄存器不为空
	while ((USART1->SR & (1 << 5)) == 0);
	//从DR中读出数据
	data = USART1->DR;
	return data;
}

/*********************************************************
*函 数 名：USART1_SendStr
*函数功能：发送一个字符串数据
*参    数：u8* str
*返 回 值：None
*备    注：
**********************************************************/
void USART1_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART1_SendByte(*str);//发送一个字节数据   //abc\0
		str++;//指针偏移
	}
	USART1_SendByte('\0');
}

/*********************************************************
*函 数 名：USART1_RecvStr
*函数功能：接收一个字符串数据
*参    数：u8* str
*返 回 值：None
*备    注：
**********************************************************/
void USART1_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART1_RecvByte();//发送一个字节数据   //abc\n
		*str = data;
		str++;
	} while (data != '\n');
	str--;
	*str = '\0';
}


USART_INFO USART1_Recv = { 0 };
/*********************************************************
*函 数 名：USART1_Recv
*函数功能：串口1接收并打印
*参    数：void
*返 回 值：void
*备    注：
**********************************************************/
void USART1_RECV(void)
{
	if (USART1_Recv.flag == 1)
	{
		USART1_Recv.flag = 0;
		printf("%s\r\n", USART1_Recv.data);
		memset(USART1_Recv.data, 0, sizeof(USART1_Recv.data));
	}
}

/*********************************************************
*函 数 名：USART1_IRQHandler
*函数功能：USART1中断
*参    数：None
*返 回 值：None
*备    注：满足USART中断触发的两个条件：
			1、中断控制位使能      2、对应的事件标志置1
**********************************************************/
void USART1_IRQHandler(void)
{
	u8 clean = 0;
	//接受中断
	if (USART1->SR&(1 << 5))
	{
		//清除标志位
		if (USART1_Recv.index < Max_Size - 1)//防止溢出
		{
			USART1_Recv.data[USART1_Recv.index] = USART1->DR;//即接受数据又能清除标志位
			USART1_Recv.index++;
		}
	}
	//空闲中断
	else if (USART1->SR&(1 << 4))
	{
		//清除标志位
		clean = USART1->SR;
		clean = USART1->DR;
		(void)clean;//去除警告
		USART1_Recv.flag = 1;
		USART1_Recv.data[USART1_Recv.index] = '\0';
		USART1_Recv.index = 0;//下标清零
	}
}
































/****************************************************
函数功能：printf重定向
参    数：None
返 回 值：None
备    注：
*****************************************************/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
	ch = ch;
}
//重定义fputc函数 
int fputc(int ch, FILE *f)
{
	USART1_SendByte(ch);
	return ch;
}

/**********************printf support end**********************/

#endif




