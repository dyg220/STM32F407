#include "wwdg.h"
/*********************************************************
*函 数 名：WWDG_Init
*函数功能：窗口看门狗初始化
*参    数：None
*返 回 值：None
*备    注：
**********************************************************/
void WWDG_Init(void)
{
	//使能看门狗时钟
	RCC->APB1ENR |= (1 << 11);

	WWDG->CFR |= (3 << 7);//八分频
	WWDG->CFR |= (0x70 << 0);//窗口值
	WWDG->CFR |= (1 << 9);//使能提前唤醒中断控制位

	WWDG->SR &= ~(1 << 0);//清除中断标志位

	WWDG->CR |= (0x7F << 0);//填入计数值

	NVIC_SetPriority(WWDG_IRQn, NVIC_EncodePriority(7 - 2, 1, 1));
	//使能中断通道
	NVIC_EnableIRQ(WWDG_IRQn);

	WWDG->CR |= (1 << 7);//使能看门狗
}


void WWDG_IRQHandler(void)
{
	if (WWDG->SR &(1 << 0))
	{
		WWDG->CR |= (0x7F << 0);//填入计数值
		LED1_FZ;
		WWDG->SR &= ~(1 << 0);//清除中断标志位
	}
}



