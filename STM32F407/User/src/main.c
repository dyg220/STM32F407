#include "main.h"                  // Device header


int main(void)
{

	NVIC_SetPriorityGrouping(7 - 2);//�������ȼ�����

	Led_Init();//LED��ʼ��
	Beep_Init();//��������ʼ��
	Fire_Init();//�����ʼ��
	Key_Init();//������ʼ��

	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);//����2��ʼ��
//	EXTI0_IRQ_Config();		//EXTI0������
//	EXTI4_IRQ_Config();		//EXTI4������
//	EXTI6_SoftIRQ_Config();	//����ж�
//	SysTick_interrupt_Init(500);

	//SysTick_Config_Own(1);

	timer6_init(5000 - 1, 8400 - 1);	//��װ��ֵ:5000-1, ��Ƶ8400-1
	while (1)
	{
		//printf("test--------------\r\n");
		//delay_xms(1000);//�ж�ʵ�ֵ���ʱ����

	}
}











