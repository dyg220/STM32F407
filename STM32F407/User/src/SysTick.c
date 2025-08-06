#include "SysTick.h"

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