#include "main.h"                  // Device header

int main(void)
{
	NVIC_SetPriorityGrouping(7-2);//�������ȼ�����
	
	Led_Init();//LED��ʼ��
	Beep_Init();//��������ʼ��
	Fire_Init();//�����ʼ��
	Key_Init();//������ʼ��
	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);//����2��ʼ��
//	HC_SR04_Init();//��������ʼ��
//	IWDG_Init();
//	TIM7_Interrupt_ms(500);	
	WWDG_Init();
	
	printf("Start��\r\n");

	while(1)
	{
		
	}
}











