#include "SysTick.h"

void systick_us(u32 xus)
{
	SysTick->CTRL &= ~(1 << 2);  //外部参考时钟
	SysTick->LOAD |= 21 * xus - 1;
	SysTick->VAL = 0; //清零
	SysTick->CTRL |= 1 << 0;	//使能systick
	while (!((SysTick->CTRL) &(1 << 16)));
	SysTick->CTRL &= ~(1 << 0);  //关闭

}

//ms延时，最大798ms
void systick_ms(u32 xms)
{
	SysTick->CTRL &= ~(1 << 2);  //外部参考时钟
	SysTick->LOAD |= 21000 * xms - 1;
	SysTick->VAL = 0; //清零
	SysTick->CTRL |= 1 << 0;	//使能systick
	while (!((SysTick->CTRL) &(1 << 16)));
	SysTick->CTRL &= ~(1 << 0);  //关闭
}

//可大于798ms
void systick_xms(u32 xms)
{
	while (xms--)
	{
		systick_ms(1);
	}
}