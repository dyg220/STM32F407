#include "exti.h"

/*********************************************************
 *函 数 名：EXTI0_IRQ_Config
 *函数功能：EXTI0线配置
 *参    数：None
 *返 回 值：None
 *备    注：
 **********************************************************/
void EXTI0_IRQ_Config(void)
{
    /*GPIO配置*/
    RCC->AHB1ENR |= (1 << 0);  // 使能时钟
    GPIOA->MODER &= ~(3 << 0); // 通用输入
    GPIOA->PUPDR &= ~(3 << 0); // 无上下拉
    /*SYSCFG配置*/
    RCC->APB2ENR |= (1 << 14);        // 使能时钟
    SYSCFG->EXTICR[0] &= ~(0xf << 0); // 配置IO映射到EXTI线上 PA0
    /*EXTI配置*/
    EXTI->RTSR |= (1 << 0); // 边沿触发选择寄存器(上升沿)
    EXTI->FTSR &= ~(1 << 0);
    EXTI->IMR |= (1 << 0); // 中断屏蔽寄存器
    /*NVIC的配置*/
    // 设置具体中断通道优先级
    NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // 使能中断通道
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0); // 清除标志位
        // 紧急程序
        // delay_ms(15);
        LED1_FZ;
    }
}

void EXTI4_IRQ_Config(void)
{
    /*GPIO配置*/
    RCC->AHB1ENR |= (1 << 0);  // 使能时钟
    GPIOA->MODER &= ~(3 << 8); // 通用输入
    GPIOA->PUPDR &= ~(3 << 8); // 无上下拉
    /*SYSCFG配置*/
    RCC->APB2ENR |= (1 << 14);        // 使能时钟
    SYSCFG->EXTICR[1] &= ~(0xf << 0); // 配置IO映射到EXTI线上
    /*EXTI配置*/
    EXTI->RTSR |= (1 << 4); // 边沿触发选择寄存器(上升沿和下降沿)
    EXTI->FTSR |= (1 << 4);
    EXTI->IMR |= (1 << 4); // 中断屏蔽寄存器
    /*NVIC的配置*/
    // 设置具体中断通道优先级
    NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // 使能中断通道
    NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI4_IRQHandler(void)
{
    if (EXTI->PR & (1 << 4)) // 判断EXTI4进来的
    {
        EXTI->PR |= (1 << 4); // 清除标志位
        // 判断是什么边沿触发的
        if (GPIOA->IDR & (1 << 4)) // 上升沿过为高电平（无火）
        {
            Beep_OFF;
        }
        else // 下降沿过后为低电平（有火）
        {
            Beep_ON;
        }
    }
}

/*********************************************************
 *函 数 名：EXTI6_SoftIRQ_Config
 *函数功能：EXTI6线软件中断配置
 *参    数：None
 *返 回 值：None
 *备    注：
 **********************************************************/
void EXTI6_SoftIRQ_Config(void)
{
    EXTI->IMR |= (1 << 6); // 中断屏蔽寄存器
    /*NVIC的配置*/
    // 设置具体中断通道优先级
    NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(7 - 2, 2, 1));
    // 使能中断通道
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1 << 6)) // 判断EXTI6进来的
    {
        EXTI->PR |= (1 << 6); // 清除PR标志位也能清SWIER
        Beep_FZ;
    }
}
