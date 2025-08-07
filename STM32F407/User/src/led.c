#include "led.h"

/*********************************************************
*函 数 名：Led_Init
*函数功能：LED初始化
*参    数：None
*返 回 值：None
*备    注：LED1---PC4  LED2---PC5  LED3---PC6  LED4---PC7
**********************************************************/
void Led_Init(void)
{
	//打开时钟
	RCC->AHB1ENR |= (1<<2);
	//配置为通用输出模式
	GPIOC->MODER &= ~((3<<8) | (3<<10) | (3<<12) | (3<<14));
	GPIOC->MODER |= ((1<<8) | (1<<10) | (1<<12) | (1<<14));
	//配置输出类型(推挽输出)
	GPIOC->OTYPER &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7));
	//配置输出速度(低速)
	GPIOC->OSPEEDR &= ~((3<<8) | (3<<10) | (3<<12) | (3<<14));
	//配置无上拉下拉
	GPIOC->PUPDR &= ~((3<<8) | (3<<10) | (3<<12) | (3<<14));
	
	Led_All_OFF();
}

/*********************************************************
*函 数 名：Led_All_ON
*函数功能：LED全开
*参    数：None
*返 回 值：None
*备    注：LED1---PC4  LED2---PC5  LED3---PC6  LED4---PC7
**********************************************************/
void Led_All_ON(void)
{
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
}

/*********************************************************
*函 数 名：Led_All_OFF
*函数功能：LED全关
*参    数：None
*返 回 值：None
*备    注：LED1---PC4  LED2---PC5  LED3---PC6  LED4---PC7
**********************************************************/
void Led_All_OFF(void)
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}

/*********************************************************
*函 数 名：Ledx_ON
*函数功能：某个LED亮
*参    数：u8 led  哪个led
*返 回 值：None
*备    注：LED1---PC4  LED2---PC5  LED3---PC6  LED4---PC7
**********************************************************/
void Ledx_ON(u8 led)
{
	switch(led)
	{
		case 1:LED1_ON;break;
		case 2:LED2_ON;break;
		case 3:LED3_ON;break;
		case 4:LED4_ON;break;
	}
}
/*********************************************************
*函 数 名：Ledx_OFF
*函数功能：某个LED灭
*参    数：u8 led  哪个led
*返 回 值：None
*备    注：LED1---PC4  LED2---PC5  LED3---PC6  LED4---PC7
**********************************************************/
void Ledx_OFF(u8 led)
{
	switch(led)
	{
		case 1:LED1_OFF;break;
		case 2:LED2_OFF;break;
		case 3:LED3_OFF;break;
		case 4:LED4_OFF;break;
	}
}

/*********************************************************
*函 数 名：Led_Water
*函数功能：流水灯
*参    数：None
*返 回 值：None
*备    注：speed(1~10) 数字越大，速度越慢
**********************************************************/
void Led_Water(u8 speed)
{
	static u8 n = 1;
	static u32 count = 0;
	
	Ledx_ON(n);
	count++;
	if(count>=speed*50000)
	{
		Ledx_OFF(n);
		n++;
		if(n>4)
		{
			n = 1;
		}
		count = 0;
	}
}














