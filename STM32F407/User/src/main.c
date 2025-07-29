#include "main.h"


int main(void)
{
	LED_Init();
	Beep_Init();
	BEEP_ON;
	delay_ms(300);
	BEEP_OFF;
	while (1)
	{
		LED_Water();

	}
	return 0;
}
