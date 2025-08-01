#include "usart2.h"


void USART2_Init(u32 baud)
{
	/*����IO��*/
	//I0��ʱ��ʹ��
	RCC->AHB1ENR = (1 << 0);
	//USART1��ʱ��ʹ��
	RCC->APB1ENR |= (1 << 17);

	//���ø���ģʽ
	GPIOA->MODER &= ~((3 << 4) | (3 << 6));
	GPIOA->MODER |= ((2 << 4) | (2 << 6));
	//����������
	GPIOA->PUPDR &= ~((3 << 4) | (3 << 6));
	//��������
	GPIOA->OTYPER &= ~((1 << 2 | (1 << 3)));
	//����ٶ�
	GPIOA->OSPEEDR &= ~((3 << 4) | (3 << 6));
	//����USART
	GPIOA->AFR[0] &= ~((0xf << 8) | (0xf << 12));
	GPIOA->AFR[0] |= ((7 << 8) | (7 << 12));

	/*����USART1*/
	//���ò�����(BRR)
	USART2->BRR = 42000000 / baud;
	//CR1
	USART2->CR1 &= ~(1 << 15);//16��������
	USART2->CR1 &= ~(1 << 12);//8λ�ֳ�
	USART2->CR1 &= ~(1 << 10);//��У��λ(�ر�)
	USART2->CR1 |= (1 << 3);//������ʹ��
	USART2->CR1 |= (1 << 2);//������ʹ��
	//CR2
	USART2->CR2 &= ~(3 << 12);//ֹͣλ��1λ��
	//USARTʹ��
	USART2->CR1 |= (1 << 13);

}

//����һ���ֽ�����
u8 USART2_RecvByte(void)
{
	u8 data = 0;
	//�ȴ��������ݼĴ�����Ϊ��
	while ((USART2->SR&(1 << 5)) == 0);
	//��DR�ж�������
	data = USART2->DR;
	return data;
}

//����һ���ֽ�����
void USART2_SendByte(u8 Byte)
{
	//�ȴ��������ݼĴ���Ϊ��
	while ((USART2->SR&(1 << 7)) == 0);
	//�����ݷ���DR
	USART2->DR = Byte;
}


void USART2_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART2_SendByte(*str);
		str++;
	}
	USART2_SendByte('\0');
}

void USART2_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART2_RecvByte();
		*str = data;
		str++;
	} while (data != '\n');
	str--;			//���յ�\n
	*str = '\0';	//��\n����
}
