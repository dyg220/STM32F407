#include "usart1.h"

/*********************************************************
*�� �� ����USART1_Init
*�������ܣ�USART1��ʼ��
*��    ����None
*�� �� ֵ��None
*��    ע��USART1_TX---PA9  USART1_RX---PA10
**********************************************************/
void USART1_Init(u32 Baud)
{
	/*����IO��*/
	//IO��ʱ��ʹ��
	RCC->AHB1ENR |= (1 << 0);
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
	USART1->BRR = 84000000 / Baud;
	//CR1
	USART1->CR1 &= ~(1 << 15);//16��������
	USART1->CR1 &= ~(1 << 12);//8λ�ֳ�
	USART1->CR1 &= ~(1 << 10);//��У��λ(�ر�)
	USART1->CR1 |= (1 << 3);//������ʹ��
	USART1->CR1 |= (1 << 2);//������ʹ��
	//CR2
	USART1->CR2 &= ~(3 << 12);//ֹͣλ��1λ��

	/*NVIC����*/
	//���þ����ж�ͨ�����ȼ�
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(7 - 2, 2, 2));
	//ʹ���ж�ͨ��
	NVIC_EnableIRQ(USART1_IRQn);

	//ʹ�ܽ����ж�+�����жϿ���λ
	USART1->CR1 |= (1 << 5);
	USART1->CR1 |= (1 << 4);

	//USARTʹ��
	USART1->CR1 |= (1 << 13);

}


/*********************************************************
*�� �� ����USART1_SendByte
*�������ܣ�����һ���ֽ�����
*��    ����u8 Byte
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART1_SendByte(u8 Byte)
{
	//�ȴ��������ݼĴ���Ϊ��
	while ((USART1->SR & (1 << 7)) == 0);
	//�����ݷ���DR
	USART1->DR = Byte;
}

/*********************************************************
*�� �� ����USART1_RecvByte
*�������ܣ�����һ���ֽ�����
*��    ����None
*�� �� ֵ��u8   �յ�������
*��    ע��
**********************************************************/
u8 USART1_RecvByte(void)
{
	u8 data = 0;
	//�ȴ��������ݼĴ�����Ϊ��
	while ((USART1->SR & (1 << 5)) == 0);
	//��DR�ж�������
	data = USART1->DR;
	return data;
}

/*********************************************************
*�� �� ����USART1_SendStr
*�������ܣ�����һ���ַ�������
*��    ����u8* str
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART1_SendStr(char* str)
{
	while (*str != '\0')
	{
		USART1_SendByte(*str);//����һ���ֽ�����   //abc\0
		str++;//ָ��ƫ��
	}
	USART1_SendByte('\0');
}

/*********************************************************
*�� �� ����USART1_RecvStr
*�������ܣ�����һ���ַ�������
*��    ����u8* str
*�� �� ֵ��None
*��    ע��
**********************************************************/
void USART1_RecvStr(char* str)
{
	u8 data = 0;
	do
	{
		data = USART1_RecvByte();//����һ���ֽ�����   //abc\n
		*str = data;
		str++;
	} while (data != '\n');
	str--;
	*str = '\0';
}


USART_INFO USART1_Recv = { 0 };
/*********************************************************
*�� �� ����USART1_Recv
*�������ܣ�����1���ղ���ӡ
*��    ����void
*�� �� ֵ��void
*��    ע��
**********************************************************/
void USART1_RECV(void)
{
	if (USART1_Recv.flag == 1)
	{
		USART1_Recv.flag = 0;
		printf("%s\r\n", USART1_Recv.data);
		memset(USART1_Recv.data, 0, sizeof(USART1_Recv.data));
	}
}

/*********************************************************
*�� �� ����USART1_IRQHandler
*�������ܣ�USART1�ж�
*��    ����None
*�� �� ֵ��None
*��    ע������USART�жϴ���������������
			1���жϿ���λʹ��      2����Ӧ���¼���־��1
**********************************************************/
void USART1_IRQHandler(void)
{
	u8 clean = 0;
	//�����ж�
	if (USART1->SR&(1 << 5))
	{
		//�����־λ
		if (USART1_Recv.index < Max_Size - 1)//��ֹ���
		{
			USART1_Recv.data[USART1_Recv.index] = USART1->DR;//�������������������־λ
			USART1_Recv.index++;
		}
	}
	//�����ж�
	else if (USART1->SR&(1 << 4))
	{
		//�����־λ
		clean = USART1->SR;
		clean = USART1->DR;
		(void)clean;//ȥ������
		USART1_Recv.flag = 1;
		USART1_Recv.data[USART1_Recv.index] = '\0';
		USART1_Recv.index = 0;//�±�����
	}
}
































/****************************************************
�������ܣ�printf�ض���
��    ����None
�� �� ֵ��None
��    ע��
*****************************************************/
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE
{
	int handle;
};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
	ch = ch;
}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	USART1_SendByte(ch);
	return ch;
}

/**********************printf support end**********************/

#endif




