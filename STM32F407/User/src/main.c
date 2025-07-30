#include "main.h"

u8 key_num = 0;
int main(void)
{
	LED_Init();
	Beep_Init();
	Fire_Init();
	//BEEP_ON;
	//delay_ms(300);
	//BEEP_OFF;
	while (1)
	{
		//LED_Water();
		/*	if (Fire_YES)
			{
				LED1_ON;
			}
			else
			{
				LED1_OFF;
			}*/
		key_num = Key_Scan();
		if (key_num == 1)
		{
			LED1_FZ;
		}
		else if (key_num == 2)
		{
			LED2_FZ;
		}
		else if (key_num == 3)
		{
			LED3_FZ;
		}
		else if (key_num == 4)
		{
			LED4_FZ;
		}
	}
	return 0;
}
