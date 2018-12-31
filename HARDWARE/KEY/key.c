#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "oled.h"
 #include "adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
//  u32 adcx;
//	u32 adcx1;
//	u32 adcx2;
//	u16 break_flag;
//	float price=0;
//	float charge=0; 
//	vu8 key=0;
//	float  weight;
//	float  weight1;
//	float  weight2;
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTC��PORTDʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;//KEY1-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 key_mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(key_mode)key_up=1;  //֧������		  
	if(key_up&&(S4_KEY0_WK_UP==1||S1_KEY1==0||S2_KEY2==0||S3_KEY3==0))//WK_UP=KEY3
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(S4_KEY0_WK_UP==1)return S4_KEY0_WK_UP_PRES;
		else if(S1_KEY1==0)return S1_KEY1_PRES;
		else if(S2_KEY2==0)return S2_KEY2_PRES;
		else if(S3_KEY3==0)return S3_KEY3_PRES;
	}else if(S4_KEY0_WK_UP==0&&S1_KEY1==1&&S2_KEY2==1&&S3_KEY3==1)key_up=1; 	    
 	return 0;// �ް�������
}


//void KEY_1(void)
//{
//	  adcx=Get_Adc_Average(ADC_Channel_1,10);
//		OLED_ShowCHinese(0,0,0);
//		OLED_ShowCHinese(17,0,1);
//		OLED_ShowCHinese(35,0,4);
//		OLED_ShowCHinese(53,0,2);
//		OLED_ShowString(0,2,"adcx:",12);
//		OLED_ShowNum(40,2,adcx,4,12);
//		weight=adcx/4.0;
//		OLED_ShowString(0,4,"weight:       g",12);
//		showFloat(55,4,weight,12); 
//		OLED_ShowString(0,6,"price:",12);
//	  OLED_ShowString(0,7,"charge:",12);
//		break_flag=0;
//		while(!break_flag)
//		{			
//			key=KEY_Scan(0);
//			if(key)
//			{
//					switch(key)
//					{
//						case WKUP_PRES:	 break_flag=1;		break;				
//						case S2_KEY1_PRES:  price+=0.1; showFloat(55,6,price,12); break;	
//						case S1_KEY0_PRES:	 price-=0.1; showFloat(55,6,price,12); break;				
//					}
//					weight=adcx/4.0;
//					showFloat(55,7,weight*price,12);
//					
//				}
//			}
//}
//void KEY_2(void)
//{
//	adcx=Get_Adc_Average(ADC_Channel_1,10);
//	adcx1=adcx;
//	adcx=Get_Adc_Average(ADC_Channel_1,10);
//	//adcx2=adcx;
//		OLED_ShowCHinese(0,0,0);
//		OLED_ShowCHinese(17,0,5);
//		OLED_ShowCHinese(35,0,2);
//		OLED_ShowString(0,2,"adcx1:",12);
//		OLED_ShowString(0,3,"adcx:",12);
//	//adcx=adcx1-adcx2;
//		OLED_ShowNum(47,2,adcx1,4,12);
//		OLED_ShowNum(40,3,adcx,4,12);
//		weight1=adcx1/4.0;
//	  weight=adcx/4.0;
//		OLED_ShowString(0,4,"weight1:       g",12);
//		OLED_ShowString(0,5,"weight:       g",12);
//		weight=weight1-weight2;
//		showFloat(63,4,weight1,12); 
//		showFloat(58,5,weight,12);
//		OLED_ShowString(0,6,"price:",12);
//	  OLED_ShowString(0,7,"charge:",12);
//		break_flag=0;	
//	while(!break_flag)
//	{	
//				key=KEY_Scan(0);
// 
//			if(key)
//			{
//					switch(key)
//					{
//						case WKUP_PRES:	 break_flag=1;		break;
//						case S2_KEY1_PRES:  price+=0.1; showFloat(55,6,price,12);break;	
//						case S1_KEY0_PRES:	 price-=0.1; showFloat(55,6,price,12); break;
//								
//					}
//					weight=(adcx-adcx1)/4.0;
//					showFloat(55,7,weight*price,12);
//					//break;
//				}
//			}
//}
//float KEY_3(void)
//{
//	adcx=Get_Adc_Average(ADC_Channel_1,10);
//	weight=adcx/4.0;
//	key=KEY_Scan(0);
// 
//			if(key)
//			{
//					switch(key)
//					{
////						case WKUP_PRES:break;
////						case KEY2_PRES:	break;
//						case KEY1_PRES:  price+=0.1; showFloat(55,6,price,12); break;	
//						//case KEY0_PRES:	  price-=0.1; showFloat(55,6,price,12); break;
//								
//					}
//					//showFloat(55,6,price,12);
//					key=1;
//					delay_ms(250);
//					showFloat(55,7,weight*price,12);
//				}
//}

//float KEY_4(void)
//{
//	adcx=Get_Adc_Average(ADC_Channel_1,10);
//	weight=adcx/4.0;
//	key=KEY_Scan(0);
// 
//			if(key)
//			{
//					switch(key)
//					{
////						case WKUP_PRES:break;
////						case KEY2_PRES:	break;
//						//case KEY1_PRES:  price+=0.1; showFloat(55,6,price,12); break;	
//					case KEY0_PRES:	  price-=0.1; showFloat(55,6,price,12); break;
//								
//					}
//					//showFloat(55,6,price,12);
//					key=1;
//					delay_ms(250);
//					showFloat(55,7,weight*price,12);
//				}
//}




