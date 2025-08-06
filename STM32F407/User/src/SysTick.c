#include "SysTick.h"
#include "led.h"
#include <stdio.h>

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

void systick_interrupt(u32 xms)
{
	//ʱ��Դѡ��
	SysTick->CTRL &= ~(1 << 2);//�ⲿ�ο�ʱ��
	//����װ��ֵ
	SysTick->LOAD = 21000 * xms - 1;
	//����������
	SysTick->VAL = 0;
	//ʹ���ж�
	SysTick->CTRL |= (1 << 1);

	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(7 - 2, 1, 1));
	//��ʱ��ʹ��
	SysTick->CTRL |= (1 << 0);
}

void SysTick_Config_Own(u8 xms)
{
	SysTick_Config(168000 * xms);   //1ms*xms
}

void SysTick_Handler(void)
{
	static u16 tick_cnt = 0;
	//�����־λ
	SysTick->VAL = 0;
	//�����¼�
	tick_cnt++;
	if (tick_cnt >= 300)  //300ms
	{
		LED1_FZ;
		tick_cnt = 0;
	}

}