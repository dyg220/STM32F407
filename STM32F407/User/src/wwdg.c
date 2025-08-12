#include "wwdg.h"
/*********************************************************
*�� �� ����WWDG_Init
*�������ܣ����ڿ��Ź���ʼ��
*��    ����None
*�� �� ֵ��None
*��    ע��
**********************************************************/
void WWDG_Init(void)
{
	//ʹ�ܿ��Ź�ʱ��
	RCC->APB1ENR |= (1 << 11);

	WWDG->CFR |= (3 << 7);//�˷�Ƶ
	WWDG->CFR |= (0x70 << 0);//����ֵ
	WWDG->CFR |= (1 << 9);//ʹ����ǰ�����жϿ���λ

	WWDG->SR &= ~(1 << 0);//����жϱ�־λ

	WWDG->CR |= (0x7F << 0);//�������ֵ

	NVIC_SetPriority(WWDG_IRQn, NVIC_EncodePriority(7 - 2, 1, 1));
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(WWDG_IRQn);

	WWDG->CR |= (1 << 7);//ʹ�ܿ��Ź�
}


void WWDG_IRQHandler(void)
{
	if (WWDG->SR &(1 << 0))
	{
		WWDG->CR |= (0x7F << 0);//�������ֵ
		LED1_FZ;
		WWDG->SR &= ~(1 << 0);//����жϱ�־λ
	}
}



