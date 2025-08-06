#include "SysTick.h"

void systick_us(u32 xus)
{
	SysTick->CTRL &= ~(1 << 2);  //�ⲿ�ο�ʱ��
	SysTick->LOAD |= 21 * xus - 1;
	SysTick->VAL = 0; //����
	SysTick->CTRL |= 1 << 0;	//ʹ��systick
	while (!((SysTick->CTRL) &(1 << 16)));
	SysTick->CTRL &= ~(1 << 0);  //�ر�

}

//ms��ʱ�����798ms
void systick_ms(u32 xms)
{
	SysTick->CTRL &= ~(1 << 2);  //�ⲿ�ο�ʱ��
	SysTick->LOAD |= 21000 * xms - 1;
	SysTick->VAL = 0; //����
	SysTick->CTRL |= 1 << 0;	//ʹ��systick
	while (!((SysTick->CTRL) &(1 << 16)));
	SysTick->CTRL &= ~(1 << 0);  //�ر�
}

//�ɴ���798ms
void systick_xms(u32 xms)
{
	while (xms--)
	{
		systick_ms(1);
	}
}