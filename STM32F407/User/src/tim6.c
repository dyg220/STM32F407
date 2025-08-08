#include "tim6.h"
#include "led.h"


/*
函数功能：基本定时器初始化
返回值：无
形参：arr：重装载值 psc：预分频值
*/
void timer6_init(u16 arr, u16 psc)
{
	//开启基本定时器6（TIM6）的时钟
	RCC->APB1ENR |= 1 << 4;

	/*清空计数器的值*/
	TIM6->CNT = 0;

	TIM6->PSC = psc;  //预分频值 （8400）
	TIM6->ARR = arr;  //重装载值 （1s钟定时）

	TIM6->CR1 = 0;      //将控制寄存器1清空

	TIM6->CR1 |= 1 << 2;    //设置事件更新请求源

	/*设置无缓冲功能*/
	TIM6->CR1 &= ~(1 << 7);

	/*设置循环模式*/
	TIM6->CR1 &= ~(1 << 3);

	/*允许更新中断使能*/
	TIM6->DIER |= 1 << 0;

	/*使能基本定时器中断*/
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	/*开启计数器使能*/
	TIM6->CR1 |= 1 << 0;

}

/*
函数功能：基本定时器终端服务函数
返回值：无
形参：无
*/
void TIM6_DAC_IRQHandler(void)
{
	if (TIM6->SR & (1 << 0))      //溢出中断
	{
		TIM6->SR &= ~(1 << 0);  //清除中断标志位
		//执行相应操作
		//LED1_FZ;
		printf("滴\r\n");
	}
}