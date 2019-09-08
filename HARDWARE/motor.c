#include "motor.h"
#include "sys.h"
#include "speed.h"
#include "remote.h"
#include "usart.h"
#include "delay.h"

//typedef const uint16_t SPEED;

//SPEED Speed0 = 0;
//SPEED Speed1 = 400;
//SPEED Speed2 = 500;
//SPEED Speed3 = 600;

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
	R=LOW;
	L=LOW;
	direction=Forward;
	delay_us(25);
	Pause();
	
}

void Backward_car(uint16_t Speed)
{
	TIM_SetCompare1(TIM3,899-Speed);
	TIM_SetCompare2(TIM2,899-Speed);
	R=HIGH;
	L=HIGH;
	direction=Backward;
	delay_us(25);
	Pause();
}

void Right_car(uint16_t speed)
{
	if(direction==Forward)
	{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM2,speed);
		R=LOW;
		L=LOW;
		delay_us(25);
		Pause();
	}
	else
	{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM2,899-speed);
		R=LOW;
		L=HIGH;
		delay_us(25);
		Pause();
	}
}

void Left_car(uint16_t speed)
{
	if(direction==Forward)
	{
		TIM_SetCompare1(TIM3,speed);
		TIM_SetCompare2(TIM2,0);
		R=LOW;
		L=LOW;
		delay_us(25);
		Pause();
	}
	else
	{
		TIM_SetCompare1(TIM3,899-speed);
		TIM_SetCompare2(TIM2,0);
		R=HIGH;
		L=LOW;
		delay_us(25);
		Pause();
	}
}

void Pause(void)
{
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM2,0);
	R=HIGH;
	L=LOW;
}

//设置速度档位

#if DISABLE

uint16_t Select_Speed(u8 value)
{
	uint16_t s;
	switch(value)
	{
		case key_1:
			s=((uint16_t)400);
		  break;
		case key_2:
			s=((uint16_t)500);
		  break;
		case key_3:
			s=((uint16_t)600);
		  break;
		default:
			break;
	}
	return s;
}

#endif

#if DISABLE

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

#endif


