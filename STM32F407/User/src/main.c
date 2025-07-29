#include "main.h"


int main(void)
{
	LED_Init();
	Beep_Init();
	//BEEP_ON;
	while (1)
	{
		LED_Water();

	}
	return 0;
}
