#include "sr04.h"

/*********************************************************
*函 数 名：HC_SR04_Init
*函数功能：超声波初始化
*参    数：None
*返 回 值：None
*备    注：PB8---TRIG      PB9---ECHO
**********************************************************/
void HC_SR04_Init(void)
{
	/*配置GPIO*/
	RCC->AHB1ENR |= (1 << 1);
	//PB8
	GPIOB->MODER &= ~(3 << 16);
	GPIOB->MODER |= (1 << 16);
	GPIOB->OTYPER &= ~(1 << 8);
	GPIOB->PUPDR &= ~(3 << 16);
	GPIOB->OSPEEDR &= ~(3 << 16);
	//PB9
	GPIOB->MODER &= ~(3 << 18);
	GPIOB->PUPDR &= ~(3 << 18);
	/*定时器的配置*/
	//定时器时钟使能
	RCC->APB1ENR |= (1 << 4);
	//CR1
	TIM6->CR1 |= (1 << 7);//开启预装载功能（影子寄存器）
	TIM6->CR1 |= (1 << 3);//开启单脉冲模式
	TIM6->CR1 &= ~(1 << 2);//更新中断触发途径
	TIM6->CR1 &= ~(1 << 1);//是否产生更新事件（是）
	//填入分频值
	TIM6->PSC = 84 - 1;//计一个数为1us
	//填入重装载值
	TIM6->ARR = 0xFFFF;
	//手动产生更新事件
	TIM6->EGR |= (1 << 0);
	//清除UIF(更新事件）标志位
	TIM6->SR &= ~(1 << 0);

	//TRIG空闲
	TRIG_L;
}



/*********************************************************
*函 数 名：HC_SR04_Read_Distance
*函数功能：超时波测距
*参    数：None
*返 回 值：距离（cm）
*备    注：
**********************************************************/
float HC_SR04_Read_Distance(void)
{
	u32 cnt = 0;
	float distance = 0;
	/*触发信号*/
	TRIG_H;
	delay_us(15);
	TRIG_L;

	/*测距*/
	while (!ECHO_Read);//等待高电平到来
	//使能定时器
	TIM6->CR1 |= (1 << 0);
	while (ECHO_Read);//等待低电平到来
	//关闭定时器
	TIM6->CR1 &= ~(1 << 0);
	cnt = TIM6->CNT;//读取计数值
	TIM6->CNT = 0;//清空计数器

	distance = (float)cnt / 58.0;
	return distance;
}







