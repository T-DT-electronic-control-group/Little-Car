#include "remote.h"

void Remote_Init(void)
{
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;
	TIM_TimeBaseInitTypeDef time;
	TIM_ICInitTypeDef ic;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &gpio);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
	
	time.TIM_Period = 10000;
	time.TIM_Prescaler = (72-1);
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &time);
	
	ic.TIM_Channel = TIM_Channel_4;
	ic.TIM_ICPolarity = TIM_ICPolarity_Rising;
	ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
	ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	ic.TIM_ICFilter = 0x03;
	TIM_ICInit(TIM4, &ic);
	
	TIM_Cmd(TIM4,ENABLE );
	
	nvic.NVIC_IRQChannel = TIM4_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic);
	
	TIM_ITConfig( TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);

}

u8 	RmtSta=0;	  	  
u16 Dval;		    //下降沿时计数器的值
u32 RmtRec=0;	  //红外接收到的数据	   		    
u8  RmtCnt=0;

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		if(RmtSta&0x80)								               //上次有数据被接收到了
		{	
			RmtSta&=~0X10;							               //取消上升沿已经被捕获标记
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;	     //标记已经完成一次按键的键值信息采集
			if((RmtSta&0X0F)<14)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);					               //清空引导标识
				RmtSta&=0XF0;						                 //清空计数器	
			}								 	   	
		}							    
	}
	if(TIM_GetITStatus(TIM4,TIM_IT_CC4)!=RESET)
	{	  
		if(RDATA)                                               //上升沿捕获
		{
  		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);   //CC4P=1	设置为下降沿捕获
			TIM_SetCounter(TIM4,0);							                  //清空定时器值
			RmtSta|=0X10;							                            //标记上升沿已经被捕获
		}
		else                                                    //下降沿捕获
		{
			Dval=TIM_GetCapture4(TIM4);					                  //读取CCR4也可以清CC4IF标志位
  		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC4P=0	设置为上升沿捕获
			if(RmtSta&0X10)							                          //完成一次高电平捕获 
			{
 				if(RmtSta&0X80)                  //接收到了引导码
				{
					if(Dval>300&&Dval<800)			   //560为标准值,560us
					{
						RmtRec<<=1;					         //左移一位.
						RmtRec|=0;					         //接收到0	   
					}
					else if(Dval>1400&&Dval<1800)  //1680为标准值,1680us
					{
						RmtRec<<=1;					         //左移一位.
						RmtRec|=1;					         //接收到1
					}
					else if(Dval>2200&&Dval<2600)  //得到按键键值增加的信息 2500为标准值2.5ms
					{
						RmtCnt++; 					         //按键次数增加1次
						RmtSta&=0XF0;				         //清空计时器		
					}
 				}
				else if(Dval>4200&&Dval<4700)	   //4500为标准值4.5ms
				{
					RmtSta|=1<<7;					         //标记成功接收到了引导码
					RmtCnt=0;						           //清除按键次数计数器
				}						 
			}
			RmtSta&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC4);	 	  	    
}

//处理信号值
u8 Remote_Scan(void)
{        
	u8 sta=0;       
    u8 t1,t2;  
	if(RmtSta&(1<<6))                   //得到一个按键的所有信息了
	{ 
	    t1=RmtRec>>24;			            //得到地址码
	    t2=(RmtRec>>16)&0xff;	          //得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;      //键值正确	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))  //按键数据错误/遥控已经没有按下了
		{
		 	RmtSta&=~(1<<6);                //清除接收到有效按键标识
			RmtCnt=0;		                    //清除按键次数计数器
		}
	}  
  return sta;
}




