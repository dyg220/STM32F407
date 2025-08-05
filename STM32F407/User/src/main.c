#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern USART_INFO USART1_Recv;
extern USART_INFO USART2_Recv;

int main(void)
{
	u8 key_num = 0;
	u8 speed = 5;
	u8 led_flag = 0;
	//设置优先级分组
	NVIC_SetPriorityGrouping(7 - 2);
	USART1_Init(115200);
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
		if (USART1_Recv.flag == 1)
		{
			USART1_Recv.flag = 0;
			printf("%s\r\n", USART1_Recv.data);
			memset(USART1_Recv.data, 0, sizeof(USART1_Recv.data));
		}


	}
	return 0;
}
