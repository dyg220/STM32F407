#include "fire.h"

//PA4 引脚
void Fire_Init(void)
{
	RCC->AHB1ENR |= 1 << 0;

	GPIOA->MODER &= ~(3 << 8);  //00 输入模式
	GPIOA->PUPDR &= ~(3 << 8);  //浮空或上拉

}
