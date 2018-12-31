#include "adc.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "schedule.h"
#include "oled.h"
	   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   

extern float adcx;  //����AD;
extern float adcx1;
extern float adcx2;
extern char is_Ready;
extern float weight;//����
extern int fur_mode; //ȥƤ��־λ 1:ȥƤ 0:��ȥƤ
extern float unit_price , price , total_price ; //����(Ԫÿ��) �۸�(Ԫ) �ܼ�(Ԫ)
extern int number ;//���ش���
int a;

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 0, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 



void D_mode1(void)//ȥƤ
{
		while(!is_Ready)
		{
//			for(a=0;a<number;a++)
//			{
				LED2=1; 
				LED3=1;
				while(KEY_Scan(0)!= S3_KEY3_PRES)//��S3ȷ��Ƥ����
				adcx1=Get_Adc_Average(ADC_Channel_1,10);
        LED2 = 0;
				while(KEY_Scan(0)!= S3_KEY3_PRES)//��S3ȷ��������
				adcx2=Get_Adc_Average(ADC_Channel_1,10);
				LED3 = 0;
				adcx = adcx2-adcx1;
				weight = adcx/4.0;
				price = weight*unit_price;
        showFloat(56,0,weight,12);
        showFloat(65,1,price,12);
				total_price+=price;
			 //}
				showFloat(54,2,total_price,16);
				is_Ready = 1;
		}
}
void D_mode0(void)//��ȥƤ
{
			while(is_Ready==0)
			{
				adcx = Get_Adc_Average(ADC_Channel_1,10);
        weight = adcx/4.0;
				price = weight*unit_price;
        showFloat(65,0,weight,12);
        showFloat(65,1,price,12);
	
				total_price+=price;
        showFloat(54,3,total_price,16);
				is_Ready=1;
			}
}

void D_mode(int fur_mode)
{
    switch(fur_mode)
		{
        case 1:D_mode1();break;
        case 0:D_mode0();break;
				default:break;
		}
}
























