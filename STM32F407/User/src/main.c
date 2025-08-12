#include "main.h"                  // Device header

int main(void)
{
	NVIC_SetPriorityGrouping(7-2);//设置优先级分组
	
	Led_Init();//LED初始化
	Beep_Init();//蜂鸣器初始化
	Fire_Init();//火焰初始化
	Key_Init();//按键初始化
	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);//串口2初始化
//	HC_SR04_Init();//超声波初始化
//	IWDG_Init();
//	TIM7_Interrupt_ms(500);	
	WWDG_Init();
	
	printf("Start！\r\n");

	while(1)
	{
		
	}
}











