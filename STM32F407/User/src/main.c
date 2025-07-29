#include "main.h"


int main(void)
{
	LED_Init();
	Beep_Init();
	//BEEP_ON;
	//delay_ms(300);
	//BEEP_OFF;
	Fire_Init();
	while (1)
	{
		LED_Water();
		if (Fire_DETECT)
		{
			BEEP_ON;
		}

	}
	return 0;
}
