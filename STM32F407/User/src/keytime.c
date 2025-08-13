#include "keytime.h"


/*********************************************************
*�� �� ����KeyTime_Init
*�������ܣ���ȡ��������ʱ���ʼ��
*��    ����None
*�� �� ֵ��None
*��    ע��KEY1----PA0----TIM5_CH1
**********************************************************/
void KeyTime_Init(void)
{
	/*GPIO����*/
	//ʹ��ʱ��
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 3);
	//��������
	GPIOA->MODER &= ~(3 << 0);
	GPIOA->MODER |= (2 << 0);
	GPIOA->PUPDR &= ~(3 << 0);
	GPIOA->AFR[0] &= ~(0xf << 0);
	GPIOA->AFR[0] |= (2 << 0);
	/*��ʱ��*/
	//��������
	TIM5->CR1 &= ~(3 << 8);//CR1( ʱ�ӷ�Ƶ���˲�����Ԥװ�أ�����ģʽ�������壨��������ʹ�ܣ�
	TIM5->CR1 |= (1 << 7);
	TIM5->CR1 &= ~(3 << 5);
	TIM5->CR1 &= ~(1 << 4);
	TIM5->CR1 &= ~(1 << 3);
	TIM5->CR1 &= ~(1 << 2);
	TIM5->CR1 &= ~(1 << 1);
	//PSC
	TIM5->PSC = 84 - 1;//��һ����1us
	//ARR
	TIM5->ARR = 0xffff;
	//ͨ������
	//SMCR
	TIM5->SMCR &= ~(7 << 0);//�ڲ�ʱ��
	//CCMR1
	TIM5->CCMR1 |= (0xf << 4);//�˲�����
	TIM5->CCMR1 &= ~(3 << 2);//�޷�Ƶ
	TIM5->CCMR1 &= ~(3 << 0);
	TIM5->CCMR1 |= (1 << 0);//ѡ�����뷽��IC1ӳ�䵽TI1��
	//DIER
	TIM5->DIER |= ((1 << 1) | (1 << 0));//ʹ�ܲ����жϺ͸����ж�
	//CCER
	TIM5->CCER &= ~((1 << 3) | (1 << 1));//�����ش���
	TIM5->CCER |= (1 << 0);//ʹ��ͨ��

	//EGR
	TIM5->EGR |= (1 << 0);//�ֶ����������¼�
	TIM5->SR &= ~(1 << 0);//������±�־λ
	TIM5->SR &= ~(1 << 1);//��������־λ
	/*NVIC������*/
	//�������ȼ��������ȷ���ж�ͨ����
	NVIC_SetPriority(TIM5_IRQn, NVIC_EncodePriority(7 - 2, 1, 0));
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(TIM5_IRQn);
	TIM5->CR1 |= (1 << 0);//��ʱ��ʹ��


}


float key_time = 0;
volatile u8 flag = 0;

void TIM5_IRQHandler(void)
{
	static u32 cnt_over = 0;
	static u16 cnt1 = 0;
	u32 cnt = 0, cnt2 = 0;

	//�ж��Ƿ��Ǹ����жϴ���
	if (TIM5->SR&(1 << 0))
	{
		//��������жϱ�־λ
		TIM5->SR &= ~(1 << 0);
		cnt_over++;
	}
	//�ж��Ƿ��ǲ����жϴ���
	if (TIM5->SR&(1 << 1))
	{
		//��������жϱ�־λ
		TIM5->SR &= ~(1 << 1);

		//�����ش���
		if (!(TIM5->CCER&(1 << 1)))
		{
			cnt1 = TIM5->CCR1;//��ȡ������ʱ����ֵ
			cnt_over = 0;//�����������
			TIM5->CCER |= (1 << 1);//����Ϊ�½��ش���
		}
		//�½��ش���
		else if (TIM5->CCER&(1 << 1))
		{
			cnt2 = TIM5->CCR1;//��ȡ������ʱ����ֵ
			TIM5->CCER &= ~(1 << 1);//����Ϊ�����ش���
			cnt = cnt_over * 65536 + cnt2 - cnt1;//�������� cnt(us)
			key_time = (float)cnt / 1000.0f;
			flag = 1;//��ʾ�ߵ�ƽ����
			cnt_over = 0;
		}
	}
}