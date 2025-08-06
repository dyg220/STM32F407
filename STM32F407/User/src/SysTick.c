#include "SysTick.h"
#include "led.h"
#include <stdio.h>

void systick_us(u32 xus)
{
	//时钟源选择
	SysTick->CTRL &= ~(1 << 2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21 * xus - 1;
	//计数器清零
	SysTick->VAL = 0;
	//定时器使能
	SysTick->CTRL |= (1 << 0);
	//等待计数结束
	while (!(SysTick->CTRL&(1 << 16)));
	//关闭定时器
	SysTick->CTRL &= ~(1 << 0);

}

//ms延时，最大798ms
void systick_ms(u32 xms)
{
	//时钟源选择
	SysTick->CTRL &= ~(1 << 2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21000 * xms - 1;
	//计数器清零
	SysTick->VAL = 0;
	//定时器使能
	SysTick->CTRL |= (1 << 0);
	//等待计数结束
	while (!(SysTick->CTRL&(1 << 16)));
	//关闭定时器
	SysTick->CTRL &= ~(1 << 0);
}

//可大于798ms
void systick_xms(u32 xms)
{
	while (xms--)
	{
		systick_ms(1);
	}
}

void systick_interrupt(u32 xms)
{
	//时钟源选择
	SysTick->CTRL &= ~(1 << 2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21000 * xms - 1;
	//计数器清零
	SysTick->VAL = 0;
	//使能中断
	SysTick->CTRL |= (1 << 1);

	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(7 - 2, 1, 1));
	//定时器使能
	SysTick->CTRL |= (1 << 0);
}

void SysTick_Config_Own(u8 xms)
{
	SysTick_Config(168000 * xms);   //1ms*xms
}

void SysTick_Handler(void)
{
	static u16 tick_cnt = 0;
	//清除标志位
	SysTick->VAL = 0;
	//紧急事件
	tick_cnt++;
	if (tick_cnt >= 300)  //300ms
	{
		LED1_FZ;
		tick_cnt = 0;
	}

}