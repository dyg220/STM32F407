#include "main.h"                  // Device header

u8 flag = 0;


int main(void)
{
	u8 keynum = 0;
	int right = 0;
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
	
	Breath_Init();


	printf("Start��\r\n");

	while(1)
	{
		if (flag == 0)
		{
			right += 1;
			Light_Set(right);
			if (right >= 100)flag = 1;
			delay_ms(10);
		}
		if (flag == 1)
		{
			right -= 1;
			Light_Set(right);
			if (right <= 0)flag = 0;
			delay_ms(10);
		}
	}
}











