#include "key.h"
#include "delay.h"

// PA0-key1 ：按下高电平
// PE2-key2 ：按下低电平
// PE3-key3 ：按下低电平
// PE4-key4 ：按下低电平

enum KEY_NUM
{
	key1_click = 1,
	key1_long_click,
	key2_click,
	key2_long_click,
	key3_click,
	key3_long_click,
	key4_click,
	key4_long_click
};

void Key_Init(void)
{
	RCC->AHB1ENR |= (1 << 0); // 使能GPIOA
	RCC->AHB1ENR |= (1 << 4); // 使能GPIOE

	GPIOA->MODER &= ~(3 << 0); // 00 输入模式
	GPIOA->PUPDR &= ~(3 << 0); // 浮空或上拉

	GPIOE->MODER &= ~(3 << 2); // 00 输入模式
	GPIOE->PUPDR &= ~(3 << 2); // 浮空或上拉

	GPIOE->MODER &= ~(3 << 3); // 00 输入模式
	GPIOE->PUPDR &= ~(3 << 3); // 浮空或上拉

	GPIOE->MODER &= ~(3 << 4); // 00 输入模式
	GPIOE->PUPDR &= ~(3 << 4); // 浮空或上拉
}

u8 Key_Scan(void)
{
	static u8 key_flag = 1; //标志位
	u8 key_num = 0;
	u32 key_count = 0;
	if (KEY1_PRESS	&& key_flag) // 初次确认
	{
		delay_ms(20);
		if (KEY1_PRESS)
		{ // 再次确认
			key_num = 1;
			key_flag = 0;
		}
	}
	// while (KEY1_PRESS); // 等待松手
	if (!KEY1_PRESS)
	{
		key_flag = 1;
	}

	return key_num;
}