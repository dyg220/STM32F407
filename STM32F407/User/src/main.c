#include "main.h"


int main(void)
{
	LED_Init();
	while (1)
	{
		for (u8 i = 0; i < 4; i++)
		{
			LED_ON(i + 1);
			delay_ms(500);
		}

		for (u8 i = 0; i < 4; i++)
		{
			LED_OFF(i + 1);
			delay_ms(500);
		}

	}
	return 0;
}
