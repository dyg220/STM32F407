#include "key.h"

/*********************************************************
*函 数 名：KEY_Init
*函数功能：按键初始化
*参    数：None
*返 回 值：None
*备    注：KEY1---PA0   按下为高
           KEY2---PE2   按下为低
		   KEY3---PE3   按下为低
           KEY4---PE4   按下为低		   
**********************************************************/
void Key_Init(void)
{
	//时钟使能
	RCC->AHB1ENR |= ((1<<0)|(1<<4));
	//配置通用输入模式
	GPIOA->MODER &= ~(3<<0);
	GPIOE->MODER &= ~((3<<4) | (3<<6) | (3<<8));
	//配置浮空输入
	GPIOA->PUPDR &= ~(3<<0);
	GPIOE->PUPDR &= ~((3<<4) | (3<<6) | (3<<8));
}

/*********************************************************
*函 数 名：Key_Scan
*函数功能：按键扫描
*参    数：None
*返 回 值：u8   键值
*备    注：
**********************************************************/
u8 Key_Scan(void)
{
	u8 keynum = 0;
	static u8 keyfalg = 1;
	if((Key1Press || Key2Press || Key3Press|| Key4Press) && keyfalg)//初次确认
	{
		delay_ms(20);//隔开抖动
		if(Key1Press)//再次确认
		{
		    keynum = 1;//赋值键值
			keyfalg = 0;//标志位锁定
		}
		else if(Key2Press)//再次确认
		{
		    keynum = 2;//赋值键值
			keyfalg = 0;//标志位锁定
		}
		else if(Key3Press)//再次确认
		{
		    keynum = 3;//赋值键值
			keyfalg = 0;//标志位锁定
		}
		else if(Key4Press)//再次确认
		{
		    keynum = 4;//赋值键值
			keyfalg = 0;//标志位锁定
		}
	}
	//按键抬起
	if(!Key1Press && !Key2Press && !Key3Press && !Key4Press)
	{
		keyfalg = 1;//标志位解锁
	}
	//返回键值
	return keynum;
}



