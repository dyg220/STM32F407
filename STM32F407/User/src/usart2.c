#include "usart2.h"

/*********************************************************
*�� �� ����USART2_Init
*�������ܣ�USART2��ʼ��
*��    ����None
*�� �� ֵ��None
*��    ע��USART2_TX---PA2  USART2_RX---PA3
**********************************************************/
void USART2_Init(u32 Baud)
{
	/*����IO��*/
	//IO��ʱ��ʹ��
	RCC->AHB1ENR |= (1 << 0);
	//USART2��ʱ��ʹ��
	RCC->APB1ENR |= (1 << 17);
	//���ø���ģʽ
	GPIOA->MODER &= ~((3 << 4) | (3 << 6));
	GPIOA->MODER |= ((2 << 4) | (2 << 6));
	//����������
	GPIOA->PUPDR &= ~((3 << 4) | (3 << 6));
	//��������
	GPIOA->OTYPER &= ~((1 << 2) | (1 << 3));
	//����ٶ�
	GPIOA->OSPEEDR &= ~((3 << 4) | (3 << 6));
	//����USART
	GPIOA->AFR[0] &= ~((0xf << 8) | (0xf << 12));
	GPIOA->AFR[0] |= ((7 << 8) | (7 << 12));

	/*����USART2*/
	//���ò�����(BRR)
	USART2->BRR = 42000000 / Baud;
	//CR1
	USART2->CR1 &= ~(1 << 15);//16��������
	USART2->CR1 &= ~(1 << 12);//8λ�ֳ�
	USART2->CR1 &= ~(1 << 10);//��У��λ(�ر�)
	USART2->CR1 |= (1 << 3);//������ʹ��
	USART2->CR1 |= (1 << 2);//������ʹ��
	//CR2
	USART2->CR2 &= ~(3 << 12);//ֹͣλ��1λ��

	/*NVIC����*/
	//���þ����ж�ͨ�����ȼ�
	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(USART2_IRQn);

	//ʹ�ܽ����ж�+�����жϿ���λ
	USART2->CR1 |= (1 << 5);
	USART2->CR1 |= (1 << 4);

	//USARTʹ��
	USART2->CR1 |= (1 << 13);
}

/*********************************************************
*�� �� ����USART2_SendByte
*�������ܣ�����һ���ֽ�����
*��    ����u8 Byte
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART2_SendByte(u8 Byte)
{
	//�ȴ��������ݼĴ���Ϊ��
	while ((USART2->SR & (1 << 7)) == 0);
	//�����ݷ���DR
	USART2->DR = Byte;
}

/*********************************************************
*�� �� ����USART2_RecvByte
*�������ܣ�����һ���ֽ�����
*��    ����None
*�� �� ֵ��u8   �յ�������
*��    ע��
**********************************************************/
u8 USART2_RecvByte(void)
{
	u8 data = 0;
	//�ȴ��������ݼĴ�����Ϊ��
	while ((USART2->SR & (1 << 5)) == 0);
	//��DR�ж�������    
	data = USART2->DR;
	return data;
}


/*********************************************************
*�� �� ����USART2_SendStr
*�������ܣ�����һ���ַ�������
*��    ����u8* str
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART2_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART2_SendByte(*str);//����һ���ֽ�����   //abc\0
		str++;//ָ��ƫ��
	}
	USART2_SendByte('\0');
}

/*********************************************************
*�� �� ����USART2_RecvStr
*�������ܣ�����һ���ַ�������
*��    ����u8* str
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART2_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART2_RecvByte();//����һ���ֽ�����   //abc\n
		*str = data;
		str++;
	} while (data != '\n');
	str--;
	*str = '\0';
}


USART_INFO USART2_Recv = { 0 };
void USART2_IRQHandler(void)
{
	u8 clean = 0;
	//�����ж�
	if (USART2->SR&(1 << 5))
	{
		//�����־λ
		if (USART2_Recv.index < Max_Size - 1)
		{
			USART2_Recv.data[USART2_Recv.index] = USART2->DR;//�������������������־λ
			USART2_Recv.index++;
		}
	}
	//�����ж�
	else if (USART2->SR&(1 << 4))
	{
		//�����־λ
		clean = USART2->SR;
		clean = USART2->DR;
		(void)clean;//ȥ������
		USART2_Recv.flag = 1;
		USART2_Recv.data[USART2_Recv.index] = '\0';
		USART2_Recv.index = 0;//�±�����
	}

}






