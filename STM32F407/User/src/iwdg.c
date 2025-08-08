#include "iwdg.h"

/*********************************************************
*函 数 名：IWDG_Init
*函数功能：独立看门狗初始化
*参    数：None
*返 回 值：None
*备    注：
**********************************************************/
void IWDG_Init(void)
{
	//使能LSI时钟
	RCC->CSR |= (1 << 0);
	//等待是否准备就绪
	while (!(RCC->CSR&(1 << 1)));

	//取消写保护
	IWDG->KR = 0x5555;
	//写分频值
	IWDG->PR |= (3 << 0);
	//装载值
	IWDG->RLR = 4000 - 1;
	//喂狗（将值更新）
	IWDG->KR = 0xAAAA;
	//使能看门狗
	IWDG->KR = 0xCCCC;
}



void IWDG_Feed(void)
{
	IWDG->KR = 0xAAAA;
	printf("喂狗成功\r\n");
}