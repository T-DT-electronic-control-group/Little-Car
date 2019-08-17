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
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}

void Road_Mode(void)
{
	u8 value=0;
	LED = 0;
	while(1)
	{
		value = Remote_Scan();
		if(Left==0&&Right==0&&Middle==1)
		{
			TIM_SetCompare1(TIM3,300);
	    TIM_SetCompare2(TIM2,300);
	    R=0;
	    L=0;
		}
		else if(Left==1&&Right==0&&Middle==0)
		{
			while(Middle==0)
			{
				TIM_SetCompare1(TIM3,250);
		    TIM_SetCompare2(TIM2,Speed0);
		    R=0;
				L=0;
		  }
		}
		else if(Left==0&&Right==1&&Middle==0)
		{
			while(Middle==0)
			{
				TIM_SetCompare1(TIM3,0);
		    TIM_SetCompare2(TIM2,250);
		    R=0;
		    L=0;
			}
		}
		if(value==key_OK)
		{
			LED = 1;
			break;
		}
	}
}





