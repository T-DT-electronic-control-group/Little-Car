#include "speed.h"

//PA.1   ����
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	TIM_OCInitTypeDef oc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	                    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_1;
	gpio.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	
	time.TIM_Period=arr;                         //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	time.TIM_Prescaler=psc;                      //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	time.TIM_ClockDivision=0;                    //����ʱ�ӷָ�:TDTS = Tck_tim
	time.TIM_CounterMode=TIM_CounterMode_Up;     //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&time);                //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	oc.TIM_OCMode = TIM_OCMode_PWM1;             //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	oc.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	oc.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
  TIM_OC2Init(TIM2,&oc);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);  //CCR1
  
	TIM_Cmd(TIM2,ENABLE); 
}

//PA.6  ����
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef time;
	TIM_OCInitTypeDef oc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	                    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_6;
	gpio.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	
	time.TIM_Period=arr;                    
	time.TIM_Prescaler=psc;                 
	time.TIM_ClockDivision=0;               
	time.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&time);           
	
	oc.TIM_OCMode = TIM_OCMode_PWM1;             
 	oc.TIM_OutputState = TIM_OutputState_Enable; 
	oc.TIM_OCPolarity = TIM_OCPolarity_High;     
  TIM_OC1Init(TIM3,&oc);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); 
 
	TIM_Cmd(TIM3,ENABLE); 
}

