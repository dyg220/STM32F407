#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern u8 usart_flag;
extern u8 usart_data[20];
extern int usart_len;
extern u8 usart2_data;

int main(void)
{
	u8 key_num = 0;
	u8 speed = 5;
	u8 led_flag = 0;
	u8 data = 0;
	//�������ȼ�����
	NVIC_SetPriorityGrouping(7 - 2);
	USART2_Init(115200);
	LED_Init();
	Beep_Init();
	Fire_Init();
	// BEEP_ON;
	// delay_ms(300);
	// BEEP_OFF;
	float a = 2.28;
	while (1)
	{
		/*	if (Fire_YES)
			{
				LED1_ON;
			}
			else
			{
				LED1_OFF;
			}
		*/
		/*key_num = Key_Scan();
				if (key_num == 1)
				{
					led_flag = 1;
				}
				if (key_num == 2)
				{
					led_flag = 0;
				}
				if ((key_num == 3) && led_flag)
				{
					speed--;
					if (speed < 1)
						speed = 1;
				}
				if ((key_num == 4) && led_flag)
				{
					speed++;
					if (speed > 10)
						speed = 10;
				}
				if (led_flag == 1)
				{
					LED_Water(speed);
				}
				if (led_flag == 0)
				{
					LED_ALLOFF();
				}*/

		LED_Water(5);
	


	}
	return 0;
}
