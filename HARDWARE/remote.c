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
u16 Dval;		    //�½���ʱ��������ֵ
u32 RmtRec=0;	  //������յ�������	   		    
u8  RmtCnt=0;

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		if(RmtSta&0x80)								               //�ϴ������ݱ����յ���
		{	
			RmtSta&=~0X10;							               //ȡ���������Ѿ���������
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;	     //����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
			if((RmtSta&0X0F)<14)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);					               //���������ʶ
				RmtSta&=0XF0;						                 //��ռ�����	
			}								 	   	
		}							    
	}
	if(TIM_GetITStatus(TIM4,TIM_IT_CC4)!=RESET)
	{	  
		if(RDATA)                                               //�����ز���
		{
  		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);   //CC4P=1	����Ϊ�½��ز���
			TIM_SetCounter(TIM4,0);							                  //��ն�ʱ��ֵ
			RmtSta|=0X10;							                            //����������Ѿ�������
		}
		else                                                    //�½��ز���
		{
			Dval=TIM_GetCapture4(TIM4);					                  //��ȡCCR4Ҳ������CC4IF��־λ
  		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC4P=0	����Ϊ�����ز���
			if(RmtSta&0X10)							                          //���һ�θߵ�ƽ���� 
			{
 				if(RmtSta&0X80)                  //���յ���������
				{
					if(Dval>300&&Dval<800)			   //560Ϊ��׼ֵ,560us
					{
						RmtRec<<=1;					         //����һλ.
						RmtRec|=0;					         //���յ�0	   
					}
					else if(Dval>1400&&Dval<1800)  //1680Ϊ��׼ֵ,1680us
					{
						RmtRec<<=1;					         //����һλ.
						RmtRec|=1;					         //���յ�1
					}
					else if(Dval>2200&&Dval<2600)  //�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
					{
						RmtCnt++; 					         //������������1��
						RmtSta&=0XF0;				         //��ռ�ʱ��		
					}
 				}
				else if(Dval>4200&&Dval<4700)	   //4500Ϊ��׼ֵ4.5ms
				{
					RmtSta|=1<<7;					         //��ǳɹ����յ���������
					RmtCnt=0;						           //�����������������
				}						 
			}
			RmtSta&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC4);	 	  	    
}

//�����ź�ֵ
u8 Remote_Scan(void)
{        
	u8 sta=0;       
    u8 t1,t2;  
	if(RmtSta&(1<<6))                   //�õ�һ��������������Ϣ��
	{ 
	    t1=RmtRec>>24;			            //�õ���ַ��
	    t2=(RmtRec>>16)&0xff;	          //�õ���ַ���� 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//����ң��ʶ����(ID)����ַ 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;      //��ֵ��ȷ	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))  //�������ݴ���/ң���Ѿ�û�а�����
		{
		 	RmtSta&=~(1<<6);                //������յ���Ч������ʶ
			RmtCnt=0;		                    //�����������������
		}
	}  
  return sta;
}




