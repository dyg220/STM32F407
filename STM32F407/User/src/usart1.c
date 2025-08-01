#include "usart1.h"

//PA9--TX
//PA10--RX
void USART1_Init(u32 baud)
{
	/*����IO��*/
	//I0��ʱ��ʹ��
	RCC->AHB1ENR = (1 << 0);
	//USART1��ʱ��ʹ��
	RCC->APB2ENR |= (1 << 4);

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


	/*����USART1*/
	//���ò�����(BRR)
	USART1->BRR = 84000000 / baud;
	//CR1
	USART1->CR1 &= ~(1 << 15);//16��������
	USART1->CR1 &= ~(1 << 12);//8λ�ֳ�
	USART1->CR1 &= ~(1 << 10);//��У��λ(�ر�)
	USART1->CR1 |= (1 << 3);//������ʹ��
	USART1->CR1 |= (1 << 2);//������ʹ��
	//CR2
	USART1->CR2 &= ~(3 << 12);//ֹͣλ��1λ��
	//USARTʹ��
	USART1->CR1 |= (1 << 13);

}

//����һ���ֽ�����
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//�ȴ��������ݼĴ�����Ϊ��
	while ((USART1->SR&(1 << 5)) == 0);
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

void USART1_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART1_SendByte(*str);
		str++;
	}
	USART1_SendByte('\0');
}

void USART1_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART1_RecvByte();
		*str = data;
		str++;
	} while (data != '\n');
	str--;			//���յ�\n
	*str = '\0';	//��\n����
}