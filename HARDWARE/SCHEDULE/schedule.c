#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "led.h"
#include "schedule.h"



u8 key;  			//����key_scan();
char step = 1;		//��ܲ����־λ
int fur_mode; //ȥƤ��־λ 1:ȥƤ 0:��ȥƤ
float unit_price = 1.0 , price = 0 , total_price = 0; //����(Ԫÿ��) �۸�(Ԫ) �ܼ�(Ԫ)
int number = 1;//���ش���
extern int i;
float adcx;  //����AD;
float adcx1;//adcxƤ
float adcx2;//adcxƤ+��
char is_Ready;
float weight;//����

void Schedule(void)
{
//	while(key=KEY_Scan(0))
//	{
			Display(step);
			if(step==1)
			{
					key=KEY_Scan(0);
					switch (key)
					{
						case S1_KEY1_PRES: 			 step=2;OLED_Clear();Display(step);fur_mode=1;break;
						case S2_KEY2_PRES: 			 step=2;OLED_Clear();Display(step);fur_mode=0;break;
					}
			}
			
			else if(step==2)
			{
				key=KEY_Scan(1);
				switch (key)
				{
						case S1_KEY1_PRES:   		 unit_price += 0.1;break;
						case S2_KEY2_PRES: 			 unit_price -= 0.1;break;
						case S3_KEY3_PRES:       step=3;OLED_Clear();Display(step);is_Ready=0;break;
						case S4_KEY0_WK_UP_PRES: step=1;OLED_Clear();Display(step);is_Ready=0;break;
				}
			}
			
			else if(step==3)
			{
				D_mode(fur_mode);
				key=KEY_Scan(0);
				switch (key)
				{
						case S3_KEY3_PRES:			 step=4;OLED_Clear();Display(step);break;
						case S4_KEY0_WK_UP_PRES: step=2;OLED_Clear();Display(step);break;
						default: break;
				}
			}
			else if(step==4)
			{
				key=KEY_Scan(0);
				switch (key)
				{
						case S4_KEY0_WK_UP_PRES:step=5;OLED_Clear();Display(step);break;
						case S3_KEY3_PRES:step=1;OLED_Clear();Display(step);number++;break;
						default: break;
				}
			}
			
			else Display(step);  
	//}
}



