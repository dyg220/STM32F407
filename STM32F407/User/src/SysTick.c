#include "systick.h"

/*********************************************************
*函 数 名：delay_us
*函数功能：systick微秒级延时
*参    数：延时的时间
*返 回 值：None
*备    注：使用外部参考时钟，最大时间约等于798ms
**********************************************************/
void delay_us(u32 xus)
{
	//时钟源选择
	SysTick->CTRL &= ~(1<<2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21*xus - 1;
	//计数器清零
	SysTick->VAL = 0;
	//定时器使能
	SysTick->CTRL |= (1<<0);
	//等待计数结束
	while(!(SysTick->CTRL&(1<<16)));
	//关闭定时器
	SysTick->CTRL &= ~(1<<0);
}

/*********************************************************
*函 数 名：delay_ms
*函数功能：systick毫秒级延时
*参    数：延时的时间
*返 回 值：None
*备    注：使用外部参考时钟，最大时间约等于798ms
**********************************************************/
void delay_ms(u16 xms)
{
	//时钟源选择
	SysTick->CTRL &= ~(1<<2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21000*xms - 1;
	//计数器清零
	SysTick->VAL = 0;
	//定时器使能
	SysTick->CTRL |= (1<<0);
	//等待计数结束
	while(!(SysTick->CTRL&(1<<16)));
	//关闭定时器
	SysTick->CTRL &= ~(1<<0);
}

/*********************************************************
*函 数 名：delay_ms
*函数功能：systick毫秒级延时
*参    数：延时的时间
*返 回 值：None
*备    注：可大于798ms
**********************************************************/
void delay_xms(u32 xms)
{
	while(xms--)
	{
		delay_ms(1);
	}
}


/*********************************************************
*函 数 名：SysTick_interrupt_Init
*函数功能：systick毫秒级定时中断
*参    数：触发中断的时间
*返 回 值：None
*备    注：使用外部参考时钟，最大时间约等于798ms
**********************************************************/
void SysTick_interrupt_Init(u16 xms)
{
	//时钟源选择
	SysTick->CTRL &= ~(1<<2);//外部参考时钟
	//设置装载值
	SysTick->LOAD = 21000*xms - 1;
	//计数器清零
	SysTick->VAL = 0;
	//使能中断
	SysTick->CTRL |= (1<<1);
	
	/*NVIC配置*/
	//设置具体中断通道优先级
	NVIC_SetPriority(SysTick_IRQn,NVIC_EncodePriority(7-2,1,1));
	
	//定时器使能
	SysTick->CTRL |= (1<<0);
}

/*********************************************************
*函 数 名：SysTick_Config_Own
*函数功能：systick毫秒级定时中断
*参    数：触发中断的时间
*返 回 值：None
*备    注：使用处理器时钟，最大时间约等于99.8ms
**********************************************************/
void SysTick_Config_Own(u8 xms)
{
	SysTick_Config(168000*xms);
}


u16 sys_cnt[10] = {0};

void SysTick_Handler(void)
{

	SysTick->VAL = 0;	//清除标志位
	//紧急事件
	sys_cnt[0]++;
	sys_cnt[1]++;
	sys_cnt[2]++;
	sys_cnt[3]++;
	sys_cnt[4]--;
	//第一件事
	if(sys_cnt[0]>=301)
	{
		LED1_FZ;
		sys_cnt[0] = 0;
	}
	//第二件事
	if(sys_cnt[1]>=520)
	{
		LED2_FZ;
		sys_cnt[1] = 0;
	}
	//第三件事
	if(sys_cnt[2]>=655)
	{
		LED3_FZ;
		sys_cnt[2] = 0;
	}
	//第四件事
	if(sys_cnt[3]>=900)
	{
		LED4_FZ;
		sys_cnt[3] = 0;
	}
}


void Sys_Interrupt_delay(u32 xms)
{
	sys_cnt[4]=xms;
	while(sys_cnt[4]);
}





