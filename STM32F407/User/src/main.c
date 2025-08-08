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
	HC_SR04_Init();//��������ʼ��
//	EXTI0_IRQ_Config();		//EXTI0������
//	EXTI4_IRQ_Config();		//EXTI4������
//	EXTI6_SoftIRQ_Config();	//����ж�
//	SysTick_interrupt_Init(500);

	//SysTick_Config_Own(1);

	TIM7_Interrupt_ms(500);
	while (1)
	{
		//printf("test--------------\r\n");
		//delay_xms(1000);//�ж�ʵ�ֵ���ʱ����
		Led_Water(4);
	}
}


