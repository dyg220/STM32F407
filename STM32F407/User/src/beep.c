#include "beep.h"

//BEEP/PE0
void  Beep_Init(void)
{
	RCC->AHB1ENR |= 1 << 4; //ʹ��GPIOE

	GPIOE->MODER &= ~(3 << 0);  //01 ͨ�����ģʽ
	GPIOE->MODER |= 1 << 0;

	GPIOE->OTYPER &= ~(1 << 0);  //�������
	GPIOE->OSPEEDR &= ~(3 << 0); //2Mhz
	GPIOE->PUPDR &= ~(3 << 0);	 //��������

}