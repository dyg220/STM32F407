#include "sg90.h"

/*********************************************************
*函 数 名：SG90_Init
*函数功能：SG90舵机初始化
*参    数：None
*返 回 值：None
*备    注：SG90----PB10----TIM2_CH3
**********************************************************/
void SG90_Init(void)
{
	RCC->AHB1ENR |= (1 << 1);//GPIO时钟使能
	RCC->APB1ENR |= (1 << 0);//TIM2时钟使能
	/*GPIO配置*/
	GPIOB->MODER &= ~(3 << 20);//复用输出
	GPIOB->MODER |= (2 << 20);
	GPIOB->OTYPER &= ~(1 << 10);
	GPIOB->OSPEEDR &= ~(3 << 20);
	GPIOB->PUPDR &= ~(3 << 20);
	GPIOB->AFR[1] &= ~(0xf << 8);
	GPIOB->AFR[1] |= (1 << 8);

	/*定时器基本配置*/
	//CR1:
	TIM2->CR1 |= (1 << 7);//预装载
	TIM2->CR1 &= ~(1 << 4);//计数方式(向上)
	TIM2->CR1 &= ~(1 << 3);//单脉冲（关）
	TIM2->CR1 &= ~(1 << 2);
	TIM2->CR1 &= ~(1 << 1);

	/*输出通道配置*/
	//SMCR: 
	TIM2->SMCR &= ~(7 << 0);//内部时钟
	//CCMR1:
	TIM2->CCMR2 &= ~(7 << 4);
	TIM2->CCMR2 |= (6 << 4);//PWM模式1
	TIM2->CCMR2 |= (1 << 3);//比较寄存器预装载使能
	TIM2->CCMR2 &= ~(3 << 0);//通道方向   
	//CCER:
	TIM2->CCER &= ~(1 << 9);//有效电平(高电平)

	TIM2->PSC = 840 - 1;//计一个数10us
	TIM2->ARR = 2000 - 1;//计数周期20ms
	TIM2->CCR3 = 0;

	TIM2->EGR |= (1 << 0);//手动产生更新事件
	TIM2->SR &= ~(1 << 0);

	TIM2->CCER |= (1 << 8);//使能通道
	TIM2->CR1 |= (1 << 0);//定时器使能
}

void SG90_SetAngle(u16 ccr)
{
	TIM2->CCR3 = ccr;
}