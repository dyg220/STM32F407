#include "keytime.h"


/*********************************************************
*函 数 名：KeyTime_Init
*函数功能：获取按键按下时间初始化
*参    数：None
*返 回 值：None
*备    注：KEY1----PA0----TIM5_CH1
**********************************************************/
void KeyTime_Init(void)
{
	/*GPIO配置*/
	//使能时钟
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 3);
	//复用输入
	GPIOA->MODER &= ~(3 << 0);
	GPIOA->MODER |= (2 << 0);
	GPIOA->PUPDR &= ~(3 << 0);
	GPIOA->AFR[0] &= ~(0xf << 0);
	GPIOA->AFR[0] |= (2 << 0);
	/*定时器*/
	//基本配置
	TIM5->CR1 &= ~(3 << 8);//CR1( 时钟分频（滤波），预装载，计数模式，单脉冲（不开），使能）
	TIM5->CR1 |= (1 << 7);
	TIM5->CR1 &= ~(3 << 5);
	TIM5->CR1 &= ~(1 << 4);
	TIM5->CR1 &= ~(1 << 3);
	TIM5->CR1 &= ~(1 << 2);
	TIM5->CR1 &= ~(1 << 1);
	//PSC
	TIM5->PSC = 84 - 1;//计一个数1us
	//ARR
	TIM5->ARR = 0xffff;
	//通道配置
	//SMCR
	TIM5->SMCR &= ~(7 << 0);//内部时钟
	//CCMR1
	TIM5->CCMR1 |= (0xf << 4);//滤波配置
	TIM5->CCMR1 &= ~(3 << 2);//无分频
	TIM5->CCMR1 &= ~(3 << 0);
	TIM5->CCMR1 |= (1 << 0);//选择输入方向，IC1映射到TI1上
	//DIER
	TIM5->DIER |= ((1 << 1) | (1 << 0));//使能捕获中断和更新中断
	//CCER
	TIM5->CCER &= ~((1 << 3) | (1 << 1));//上升沿触发
	TIM5->CCER |= (1 << 0);//使能通道

	//EGR
	TIM5->EGR |= (1 << 0);//手动产生更新事件
	TIM5->SR &= ~(1 << 0);//清除更新标志位
	TIM5->SR &= ~(1 << 1);//清除捕获标志位
	/*NVIC的配置*/
	//设置优先级（编码和确定中断通道）
	NVIC_SetPriority(TIM5_IRQn, NVIC_EncodePriority(7 - 2, 1, 0));
	//使能中断通道
	NVIC_EnableIRQ(TIM5_IRQn);
	TIM5->CR1 |= (1 << 0);//定时器使能


}


