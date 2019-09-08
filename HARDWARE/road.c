#include "road.h"

void Road_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOC, &gpio);
	
	LED_OFF;
	GPIO_SetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}


void Road_Mode(void)
{
	u8 value=0;
//	ROAD_Mode mode;
//	int status=10;
	LED_ON;
	
	R=LOW;
	L=LOW;
	
	while(1)
	{
		value = Remote_Scan();
	
		if(Left==WRITE&&Middle==BLACK&&Right==WRITE)
		{
			Right_Value_250;
			Left_Value_250;
		}
		
		else if(Left==BLACK&&Middle==WRITE&&Right==WRITE)
		{
			Right_Value_200;
			Left_Value_100;
		}
		
		else if(Left==WRITE&&Middle==WRITE&&Right==BLACK)
		{
			Right_Value_100;
			Left_Value_200;
		}
		
		else if(Left==WRITE&&Middle==WRITE&&Right==WRITE)
			Pause();
		
		else if(Left==BLACK&&Middle==BLACK&&Right==BLACK)
			Pause();
		
		if(value==key_OK)
		{
			LED_OFF;
			break;
		}
		delay_us(10);
	}
}





