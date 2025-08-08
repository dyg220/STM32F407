#include "tim7.h"

/*********************************************************
*�� �� ����TIM7_Interrupt_ms
*�������ܣ�TIM7��ʱ�ж�
*��    ����Ҫ�жϵ�ʱ����
*�� �� ֵ��None
*��    ע��
**********************************************************/
void TIM7_Interrupt_ms(u32 xms)
{
	//��ʱ��ʱ��ʹ��
	RCC->APB1ENR |= (1 << 5);
	//CR1
	TIM7->CR1 |= (1 << 7);//����Ԥװ�ع��ܣ�Ӱ�ӼĴ�����
	TIM7->CR1 &= ~(1 << 3);//�رյ�����ģʽ
	TIM7->CR1 &= ~(1 << 2);//�����жϴ���;��
	TIM7->CR1 &= ~(1 << 1);//�Ƿ���������¼����ǣ�
	//�����Ƶֵ
	TIM7->PSC = 8400 - 1;//��һ����Ϊ100us
	//������װ��ֵ
	TIM7->ARR = 10 * xms - 1;
	//�ֶ����������¼�
	TIM7->EGR |= (1 << 0);
	//���UIF(�����¼�����־λ
	TIM7->SR &= ~(1 << 0);

	/*NVIC������*/
	//���þ����ж�ͨ�����ȼ�
	NVIC_SetPriority(TIM7_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(TIM7_IRQn);

	//ʹ�ܸ����ж�
	TIM7->DIER |= (1 << 0);

	//ʹ�ܶ�ʱ��
	TIM7->CR1 |= (1 << 0);
}

void TIM7_IRQHandler(void)
{
	float distance = 0;
	if (TIM7->SR&(1 << 0))
	{
		TIM7->SR &= ~(1 << 0);
		distance = HC_SR04_Read_Distance();
		printf("���룺%.1fcm\r\n", distance);
	}


}




