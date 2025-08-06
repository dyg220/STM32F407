#include "SysTick.h"

void systick_us(u32 xus)
{
	//ʱ��Դѡ��
	SysTick->CTRL &= ~(1 << 2);//�ⲿ�ο�ʱ��
	//����װ��ֵ
	SysTick->LOAD = 21 * xus - 1;
	//����������
	SysTick->VAL = 0;
	//��ʱ��ʹ��
	SysTick->CTRL |= (1 << 0);
	//�ȴ���������
	while (!(SysTick->CTRL&(1 << 16)));
	//�رն�ʱ��
	SysTick->CTRL &= ~(1 << 0);

}

//ms��ʱ�����798ms
void systick_ms(u32 xms)
{
	//ʱ��Դѡ��
	SysTick->CTRL &= ~(1 << 2);//�ⲿ�ο�ʱ��
	//����װ��ֵ
	SysTick->LOAD = 21000 * xms - 1;
	//����������
	SysTick->VAL = 0;
	//��ʱ��ʹ��
	SysTick->CTRL |= (1 << 0);
	//�ȴ���������
	while (!(SysTick->CTRL&(1 << 16)));
	//�رն�ʱ��
	SysTick->CTRL &= ~(1 << 0);
}

//�ɴ���798ms
void systick_xms(u32 xms)
{
	while (xms--)
	{
		systick_ms(1);
	}
}