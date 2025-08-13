#include "main.h" // Device header

//u8 flag = 0;

extern float key_time;
extern volatile u8 flag;


// �򻯰�HSVתRGB���������⸡�����㣩
void HSVtoRGB(uint16_t h, uint8_t *r, uint8_t *g, uint8_t *b)
{
	// ��ɫ��ֳ�6��60������ (0-1530���൱��0-360���4.25)
	uint8_t sector = h / 256; // 256=60������ (1530/6=255)
	uint8_t frac = h % 256;   // ������λ��

	uint8_t p = 0;
	uint8_t q = (255 * (256 - frac)) >> 8; // ��Ч��255*(1-frac)
	uint8_t t = (255 * frac) >> 8;         // ��Ч��255*frac

	switch (sector)
	{
	case 0:
		*r = 255;
		*g = t;
		*b = p;
		break; // �����
	case 1:
		*r = q;
		*g = 255;
		*b = p;
		break; // �ơ���
	case 2:
		*r = p;
		*g = 255;
		*b = t;
		break; // �̡���
	case 3:
		*r = p;
		*g = q;
		*b = 255;
		break; // �����
	case 4:
		*r = t;
		*g = p;
		*b = 255;
		break; // ������
	case 5:
		*r = 255;
		*g = p;
		*b = q;
		break; // �ϡ���
	default:
		*r = 255;
		*g = 0;
		*b = 0;
		break; // �������
	}
}

int main(void)
{
	u8 keynum = 0;
	u8 angle = 0;
	uint16_t hue = 0;
	int right = 0;
	NVIC_SetPriorityGrouping(7 - 2); // �������ȼ�����

	Led_Init();          // LED��ʼ��
	Beep_Init();         // ��������ʼ��
	Fire_Init();         // �����ʼ��
	Key_Init();          // ������ʼ��
	USART1_Init(115200); // ����1��ʼ��
	USART2_Init(115200); // ����2��ʼ��
	//	HC_SR04_Init();		//��������ʼ��
	//	IWDG_Init();
	//	TIM7_Interrupt_ms(500);
	//	WWDG_Init();

	Breath_Init();
	SG90_Init();
	RGB_Init();
	RGB_SetColor(0, 0, 0);
	KeyTime_Init();
	printf("Start��\r\n");

	while (1)
	{
		/*if (flag == 0)
		{
			right += 1;
			Light_Set(right);
			if (right >= 100)flag = 1;
			delay_ms(10);
		}
		if (flag == 1)
		{
			right -= 1;
			Light_Set(right);
			if (right <= 0)flag = 0;
			delay_ms(10);
		}*/

		// keynum = Key_Scan();
		// if (keynum == 1)
		//{
		//	angle += 50;
		//	if (angle > 250) { angle = 50; }
		//	SG90_SetAngle(angle);
		// }
		// if (keynum == 2)
		//{
		//	angle -= 50;
		//	if (angle < 50) { angle = 250; }
		//	SG90_SetAngle(angle);
		// }

		//// ����ɫ�ࣨÿ������1��Լ0.24�㣩
		//hue++;
		//if (hue >= 1530)
		//    hue = 0; // 1530 = 6��255

		//// ת��HSV��RGB
		//uint8_t r, g, b;
		//HSVtoRGB(hue, &r, &g, &b);

		//// ����RGB��ɫ
		//RGB_SetColor(r, g, b);

		//// ����ʱ������ѭ��������
		//delay_ms(5);

		/*keynum = Key_Scan();
		if (keynum == 1)
		{
			RGB_SetColor(255, 0, 0);
		}
		if (keynum == 2)
		{
			RGB_SetColor(0, 255, 0);
		}
		if (keynum == 3)
		{
			RGB_SetColor(0, 0, 255);
		}
		if (keynum == 4)
		{
			RGB_SetColor(242, 63, 114);
		}*/
		if (flag == 1)
		{
			flag = 0;
			printf("time:%.1fms\r\n", key_time);
		}

	}
}
