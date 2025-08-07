#include "exti.h"

/*********************************************************
 *�� �� ����EXTI0_IRQ_Config
 *�������ܣ�EXTI0������
 *��    ����None
 *�� �� ֵ��None
 *��    ע��
 **********************************************************/
void EXTI0_IRQ_Config(void)
{
    /*GPIO����*/
    RCC->AHB1ENR |= (1 << 0);  // ʹ��ʱ��
    GPIOA->MODER &= ~(3 << 0); // ͨ������
    GPIOA->PUPDR &= ~(3 << 0); // ��������
    /*SYSCFG����*/
    RCC->APB2ENR |= (1 << 14);        // ʹ��ʱ��
    SYSCFG->EXTICR[0] &= ~(0xf << 0); // ����IOӳ�䵽EXTI���� PA0
    /*EXTI����*/
    EXTI->RTSR |= (1 << 0); // ���ش���ѡ��Ĵ���(������)
    EXTI->FTSR &= ~(1 << 0);
    EXTI->IMR |= (1 << 0); // �ж����μĴ���
    /*NVIC������*/
    // ���þ����ж�ͨ�����ȼ�
    NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // ʹ���ж�ͨ��
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0); // �����־λ
        // ��������
        // delay_ms(15);
        LED1_FZ;
    }
}

void EXTI4_IRQ_Config(void)
{
    /*GPIO����*/
    RCC->AHB1ENR |= (1 << 0);  // ʹ��ʱ��
    GPIOA->MODER &= ~(3 << 8); // ͨ������
    GPIOA->PUPDR &= ~(3 << 8); // ��������
    /*SYSCFG����*/
    RCC->APB2ENR |= (1 << 14);        // ʹ��ʱ��
    SYSCFG->EXTICR[1] &= ~(0xf << 0); // ����IOӳ�䵽EXTI����
    /*EXTI����*/
    EXTI->RTSR |= (1 << 4); // ���ش���ѡ��Ĵ���(�����غ��½���)
    EXTI->FTSR |= (1 << 4);
    EXTI->IMR |= (1 << 4); // �ж����μĴ���
    /*NVIC������*/
    // ���þ����ж�ͨ�����ȼ�
    NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // ʹ���ж�ͨ��
    NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI4_IRQHandler(void)
{
    if (EXTI->PR & (1 << 4)) // �ж�EXTI4������
    {
        EXTI->PR |= (1 << 4); // �����־λ
        // �ж���ʲô���ش�����
        if (GPIOA->IDR & (1 << 4)) // �����ع�Ϊ�ߵ�ƽ���޻�
        {
            Beep_OFF;
        }
        else // �½��ع���Ϊ�͵�ƽ���л�
        {
            Beep_ON;
        }
    }
}

/*********************************************************
 *�� �� ����EXTI6_SoftIRQ_Config
 *�������ܣ�EXTI6������ж�����
 *��    ����None
 *�� �� ֵ��None
 *��    ע��
 **********************************************************/
void EXTI6_SoftIRQ_Config(void)
{
    EXTI->IMR |= (1 << 6); // �ж����μĴ���
    /*NVIC������*/
    // ���þ����ж�ͨ�����ȼ�
    NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // ʹ���ж�ͨ��
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1 << 6)) // �ж�EXTI6������
    {
        EXTI->PR |= (1 << 6); // ���PR��־λҲ����SWIER
        Beep_FZ;
    }
}
