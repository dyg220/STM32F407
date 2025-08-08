#include "tim7.h"

/*********************************************************
*函 数 名：TIM7_Interrupt_ms
*函数功能：TIM7定时中断
*参    数：要中断的时间间隔
*返 回 值：None
*备    注：
**********************************************************/
void TIM7_Interrupt_ms(u32 xms)
{
	//定时器时钟使能
	RCC->APB1ENR |= (1 << 5);
	//CR1
	TIM7->CR1 |= (1 << 7);//开启预装载功能（影子寄存器）
	TIM7->CR1 &= ~(1 << 3);//关闭单脉冲模式
	TIM7->CR1 &= ~(1 << 2);//更新中断触发途径
	TIM7->CR1 &= ~(1 << 1);//是否产生更新事件（是）
	//填入分频值
	TIM7->PSC = 8400 - 1;//计一个数为100us
	//填入重装载值
	TIM7->ARR = 10 * xms - 1;
	//手动产生更新事件
	TIM7->EGR |= (1 << 0);
	//清除UIF(更新事件）标志位
	TIM7->SR &= ~(1 << 0);

	/*NVIC的配置*/
	//设置具体中断通道优先级
	NVIC_SetPriority(TIM7_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
	//使能中断通道
	NVIC_EnableIRQ(TIM7_IRQn);

	//使能更新中断
	TIM7->DIER |= (1 << 0);

	//使能定时器
	TIM7->CR1 |= (1 << 0);
}

void TIM7_IRQHandler(void)
{
	float distance = 0;
	if (TIM7->SR&(1 << 0))
	{
		TIM7->SR &= ~(1 << 0);
		distance = HC_SR04_Read_Distance();
		printf("距离：%.1fcm\r\n", distance);
	}


}




