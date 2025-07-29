#include "key.h"
#include "delay.h"

//PA0-key1 �����¸ߵ�ƽ
//PE2-key2 �����µ͵�ƽ
//PE3-key3 �����µ͵�ƽ
//PE4-key4 �����µ͵�ƽ

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
	RCC->AHB1ENR |= (1 << 0);  //ʹ��GPIOA
	RCC->AHB1ENR |= (1 << 4);  //ʹ��GPIOE

	GPIOA->MODER &= ~(3 << 0);  //00 ����ģʽ
	GPIOA->PUPDR &= ~(3 << 0);  //���ջ�����

	GPIOE->MODER &= ~(3 << 2);  //00 ����ģʽ
	GPIOE->PUPDR &= ~(3 << 2);  //���ջ�����

	GPIOE->MODER &= ~(3 << 3);  //00 ����ģʽ
	GPIOE->PUPDR &= ~(3 << 3);  //���ջ�����

	GPIOE->MODER &= ~(3 << 4);  //00 ����ģʽ
	GPIOE->PUPDR &= ~(3 << 4);  //���ջ�����

}

u8 Key_Scan(void)
{
	u8 key_num = 0;
	u32 key_count = 0;
	if (KEY1_PRESS)
	{
		delay_us(200);
		if (KEY1_PRESS)
		{
			key_num = 1;
			key_count++;
			if (key_count > 500)
			{
				key_num = 2;
			}
		}
	}

	return key_num;
}