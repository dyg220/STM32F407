#include "key.h"

/*********************************************************
*�� �� ����KEY_Init
*�������ܣ�������ʼ��
*��    ����None
*�� �� ֵ��None
*��    ע��KEY1---PA0   ����Ϊ��
           KEY2---PE2   ����Ϊ��
		   KEY3---PE3   ����Ϊ��
           KEY4---PE4   ����Ϊ��		   
**********************************************************/
void Key_Init(void)
{
	//ʱ��ʹ��
	RCC->AHB1ENR |= ((1<<0)|(1<<4));
	//����ͨ������ģʽ
	GPIOA->MODER &= ~(3<<0);
	GPIOE->MODER &= ~((3<<4) | (3<<6) | (3<<8));
	//���ø�������
	GPIOA->PUPDR &= ~(3<<0);
	GPIOE->PUPDR &= ~((3<<4) | (3<<6) | (3<<8));
}

/*********************************************************
*�� �� ����Key_Scan
*�������ܣ�����ɨ��
*��    ����None
*�� �� ֵ��u8   ��ֵ
*��    ע��
**********************************************************/
u8 Key_Scan(void)
{
	u8 keynum = 0;
	static u8 keyfalg = 1;
	if((Key1Press || Key2Press || Key3Press|| Key4Press) && keyfalg)//����ȷ��
	{
		delay_ms(20);//��������
		if(Key1Press)//�ٴ�ȷ��
		{
		    keynum = 1;//��ֵ��ֵ
			keyfalg = 0;//��־λ����
		}
		else if(Key2Press)//�ٴ�ȷ��
		{
		    keynum = 2;//��ֵ��ֵ
			keyfalg = 0;//��־λ����
		}
		else if(Key3Press)//�ٴ�ȷ��
		{
		    keynum = 3;//��ֵ��ֵ
			keyfalg = 0;//��־λ����
		}
		else if(Key4Press)//�ٴ�ȷ��
		{
		    keynum = 4;//��ֵ��ֵ
			keyfalg = 0;//��־λ����
		}
	}
	//����̧��
	if(!Key1Press && !Key2Press && !Key3Press && !Key4Press)
	{
		keyfalg = 1;//��־λ����
	}
	//���ؼ�ֵ
	return keynum;
}



