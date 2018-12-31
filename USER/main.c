#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"	 
#include "adc.h"
#include "schedule.h" 
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
************************************************/


 
 int main(void)
 {
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��	 
 	Adc_Init();		  		//ADC��ʼ��
	KEY_Init();
	OLED_Init();
  OLED_Clear();
	Display(1);
	while(1)
	{
			Schedule();
	
	}
	
 }

