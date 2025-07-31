#include "usart1.h"

//PA9--TX
//PA10--RX
void USART1_Init(u32 baud)
{
	/*����IO��*/
	//I0��ʱ��ʹ��
	RCC->AHB1ENR = (1 << 0);
	//���ø���ģʽ
	GPIOA->MODER &= ~((3 << 18) | (3 << 20));
	GPIOA->MODER |= ((2 << 18) | (2 << 20));
	//����������
	GPIOA->PUPDR &= ~((3 << 18) | (3 << 20));
	//��������
	GPIOA->OTYPER &= ~((1 << 9) | (1 << 10));
	//����ٶ�
	GPIOA->OSPEEDR &= ~((3 << 18) | (3 << 20));
	//����USART
	GPIOA->AFR[1] &= ~((0xf << 4) | (0xf << 8));
	GPIOA->AFR[1] |= ((7 << 4) | (7 << 8));


}

//����һ���ֽ�����
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//�ȴ��������ݼĴ�����Ϊ��
	while ((USART1->SR &(1 << 5)) == 0);
	//��DR�ж�������
	data = USART1->DR;
	return data;
}

//����һ���ֽ�����
void USART1_SendByte(u8 Byte)
{
	//�ȴ��������ݼĴ���Ϊ��
	while ((USART1->SR&(1 << 7)) == 0);
	//�����ݷ���DR
	USART1->DR = Byte;
}