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
	ROAD_Mode mode;
	int status=10;
	LED_ON;
	while(1)
	{
		value = Remote_Scan();
		if(Left==0&&Right==0&&Middle==1)
		{
			mode = Mode1;
			
			if(status!=mode)
				Pause();
			Right_Value_250;
			Left_Value_250;
			R=0;
	    L=0;
			status = mode;
		}
		else if(Left==1&&Right==0&&Middle==0)
		{
			while(Middle==0)
			{
				mode = Mode2;
				if(status!=mode)
					Pause();
				Right_Value_200;
				Left_Value_100;
		    R=0;
				L=0;
				status = mode;
		  }
		}
		else if(Left==0&&Right==1&&Middle==0)
		{
			while(Middle==0)
			{
				mode = Mode3;
				if(status!=mode)
					Pause();
				Right_Value_100;
				Left_Value_200;
		    R=0;
		    L=0;
				status = mode;
			}
		}
		if(value==key_OK)
		{
			LED_OFF;
			break;
		}
	}
}





