#include "main.h"                  // Device header


int main(void)
{

	NVIC_SetPriorityGrouping(7 - 2);//设置优先级分组

	Led_Init();//LED初始化
	Beep_Init();//蜂鸣器初始化
	Fire_Init();//火焰初始化
	Key_Init();//按键初始化

	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);//串口2初始化
//	EXTI0_IRQ_Config();		//EXTI0线配置
//	EXTI4_IRQ_Config();		//EXTI4线配置
//	EXTI6_SoftIRQ_Config();	//软件中断
//	SysTick_interrupt_Init(500);

	//SysTick_Config_Own(1);

	timer6_init(5000 - 1, 8400 - 1);	//重装载值:5000-1, 分频8400-1
	while (1)
	{
		//printf("test--------------\r\n");
		//delay_xms(1000);//中断实现的延时函数

	}
}











