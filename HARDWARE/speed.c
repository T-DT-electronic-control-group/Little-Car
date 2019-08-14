#include "speed.h"

//PA.1   左轮
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
	
	time.TIM_Period=arr;                         //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	time.TIM_Prescaler=psc;                      //设置用来作为TIMx时钟频率除数的预分频值 
	time.TIM_ClockDivision=0;                    //设置时钟分割:TDTS = Tck_tim
	time.TIM_CounterMode=TIM_CounterMode_Up;     //TIM向上计数模式
	TIM_TimeBaseInit(TIM2,&time);                //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	oc.TIM_OCMode = TIM_OCMode_PWM1;             //选择定时器模式:TIM脉冲宽度调制模式2
 	oc.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	oc.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
  TIM_OC2Init(TIM2,&oc);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);  //CCR1
  
	TIM_Cmd(TIM2,ENABLE); 
}

//PA.6  右轮
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

