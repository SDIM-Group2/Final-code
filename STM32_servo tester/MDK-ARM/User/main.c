/*
=============���������==============
	оƬSTM32F103C8T6��ʹ��ADC��ȡ��λ���ĵ�ѹ����ֵ��0~4095ת����1000~2000����ֵ��PWM�����
					 TIM2��ʱ����ADC������ͨ��DMA���������ch1Value��ȡ10�ν��о�ֵ�˲���
	���ƶ����PWM������20ms���ߵ�ƽʱ��0.5ms~2.5ms�仯���ɿ��ƶ��0~180��ĽǶȱ仯��
				   ����ģ�����ʵ�ʿ����У���������180��仯������ͨ�õĸߵ�ƽ�����ʵ��1ms~2ms
	��λ����GND - PA0 - 3.3V
	OLED��ʾ����
				GND   ��Դ��
				VCC   ��3.3v��Դ
				SCL   ��PB8��SCL��
				SDA   ��PB9��SDA��
	����USB-TTL�ӷ���	
				GND   ��Դ��
				3V3   ��3.3v
				TXD   ��PB7
				RXD   ��PB6
	ST-LINK V2�ӷ���
				GND   ��Դ��
				3V3   ��3.3v
				SWCLK ��DCLK
				SWDIO ��DIO
	PWM�����PB5
	by Bilibili ����CaiZi
*/
#include "config.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x.h"
#include "oled.h"
#include "rtc.h" 
#include "stdio.h"
#include "string.h"

int main()
{
	u8 txt[16]={0};
	delay_init();//��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2��2λ��ռ���ȼ���2λ�����ȼ�
	usart_init(115200);//��ʼ������1��������Ϊ115200
	TIM3_PWM_Init(19999,71);//Ԥ��Ƶ72��Ƶ��1MHz������1us���Զ�װ��ֵ20 000����PWM����1us*20 000
	TIM2_Init(499,71);//1MHz��ÿ500us�ɼ�һ�Σ�������9us���ϣ�����СӰ��OLED��ʾ
	DMA1_Init();	//DMA��ʼ��
	GPIOA_Init();	//PA��ʼ��
	Adc_Init();		//ADC��ʼ��
	RTC_Init();	  	//RTC��ʼ��
	OLED_Init();	//��ʼ��OLED  
	OLED_Clear();

	while (1){
		itoa(PWM1value,txt,10);//��int����ת����10�����ַ���
//		printf("����ֵ��%d\t������%s\t",ch1Value,txt);
//		printf("��ǰʱ�䣺%d:%d:%d\n",calendar.hour,calendar.min,calendar.sec);
		//OLED_Clear();//һֱ�����������˸
		strcat(txt," us");//�ϲ��ַ���
		OLED_ShowString(6,3,txt,24); //λ��6,3���ַ���С24*24����
		OLED_Refresh_Gram();
		delay_ms(1);
	}
}
