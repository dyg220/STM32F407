#include "fire.h"

//PA4 ����
void Fire_Init(void)
{
	RCC->AHB1ENR |= 1 << 0;

	GPIOA->MODER &= ~(3 << 8);  //00 ����ģʽ
	GPIOA->PUPDR &= ~(3 << 8);  //���ջ�����

}
