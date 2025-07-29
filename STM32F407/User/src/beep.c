#include "beep.h"

//BEEP/PE0
void  Beep_Init(void)
{
	RCC->AHB1ENR |= 1 << 4; //使能GPIOE

	GPIOE->MODER &= ~(3 << 0);  //01 通用输出模式
	GPIOE->MODER |= 1 << 0;

	GPIOE->OTYPER &= ~(1 << 0);  //推挽输出
	GPIOE->OSPEEDR &= ~(3 << 0); //2Mhz
	GPIOE->PUPDR &= ~(3 << 0);	 //无上下拉

}