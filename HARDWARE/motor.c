#include "motor.h"
#include "sys.h"
#include "speed.h"
#include "remote.h"
#include "usart.h"
#include "delay.h"

enum Direction direction;

//初始化L298n使能端
void L298n_Init(void)
{
	GPIO_InitTypeDef gpio;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&gpio);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	
	direction = Forward;
}

void Forward_car(uint16_t Speed)
{
	TIM_SetCompare1(TIM3,Speed);
	TIM_SetCompare2(TIM2,Speed);
	R=0;
	L=0;
	direction=Forward;
	delay_us(25);
	Pause();
	
}

void Backward_car(uint16_t Speed)
{
	TIM_SetCompare1(TIM3,899-Speed);
	TIM_SetCompare2(TIM2,899-Speed);
	R=1;
	L=1;
	direction=Backward;
	delay_us(25);
	Pause();
	
}

void Right_car(uint16_t speed)
{
	if(direction==Forward)
	{
		TIM_SetCompare1(TIM3,Speed0);
		TIM_SetCompare2(TIM2,speed);
		R=0;
		L=0;
		delay_us(25);
		Pause();
	}
	else
	{
		TIM_SetCompare1(TIM3,Speed0);
		TIM_SetCompare2(TIM2,899-speed);
		R=0;
		L=1;
		delay_us(25);
		Pause();
	}
}

void Left_car(uint16_t speed)
{
	if(direction==Forward)
	{
		TIM_SetCompare1(TIM3,speed);
		TIM_SetCompare2(TIM2,Speed0);
		R=0;
		L=0;
		delay_us(25);
		Pause();
	}
	else
	{
		TIM_SetCompare1(TIM3,899-speed);
		TIM_SetCompare2(TIM2,Speed0);
		R=1;
		L=0;
		delay_us(25);
		Pause();
	}
}

void Pause(void)
{
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM2,0);
	R=1;
	L=0;
}

//设置速度档位
uint16_t Select_Speed(u8 value)
{
	uint16_t s;
	switch(value)
	{
		case key_1:
			s=Speed1;
		  break;
		case key_2:
			s=Speed2;
		  break;
		case key_3:
			s=Speed3;
		  break;
		default:
			break;
	}
	return s;
}


