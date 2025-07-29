#include "led.h"

void LED_Init(void)
{
	RCC->AHB1ENR |= 1 << 2;		//ʹ��GPIOC
	//LED1~LED4 - PC4~PC7
	GPIOC->MODER &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14));	//ͨ�����ģʽ
	GPIOC->MODER |= (1 << 8) | (1 << 10) | (1 << 12) | (1 << 14);

	GPIOC->OTYPER &= ~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));		//�������
	GPIOC->OSPEEDR &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14));  //����ģʽ
	GPIOC->PUPDR &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14));	//������������

	LED_ALLOFF();
}

void LED_ALLOFF(void)
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}

void LED_ALLON(void)
{
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
}


//��ˮ��
void LED_Water(void)
{
	for (u8 i = 0; i < 4; i++)
	{
		LED_ON(i + 1);
		delay_ms(500);
	}

	for (u8 i = 0; i < 4; i++)
	{
		LED_OFF(i + 1);
		delay_ms(500);
	}

}

void LED_ON(u8 num)
{
	switch (num)
	{
	case 1:
		LED1_ON;
		break;
	case 2:
		LED2_ON;
		break;
	case 3:
		LED3_ON;
		break;
	case 4:
		LED4_ON;
		break;
	default:
		break;
	}
}

void LED_OFF(u8 num)
{
	switch (num)
	{
	case 1:
		LED1_OFF;
		break;
	case 2:
		LED2_OFF;
		break;
	case 3:
		LED3_OFF;
		break;
	case 4:
		LED4_OFF;
		break;
	default:
		break;
	}
}