#ifndef __SPEED_H__
#define __SPEED_H__

#include "sys.h"

//使用 TIM3_CH1  PA.6
void TIM3_PWM_Init(u16 arr,u16 psc);


//使用 TIM2_CH2  PA.1
void TIM2_PWM_Init(u16 arr,u16 psc);


#define Right_Value_500 TIM_SetCompare1(TIM3,500)
#define Left_Value_500  TIM_SetCompare2(TIM2,500)
#define Right_Value_400 TIM_SetCompare1(TIM3,400)
#define Left_Value_400  TIM_SetCompare2(TIM2,400)
#define Right_Value_350 TIM_SetCompare1(TIM3,350)
#define Left_Value_350  TIM_SetCompare2(TIM2,350)
#define Right_Value_300 TIM_SetCompare1(TIM3,300)
#define Left_Value_300  TIM_SetCompare2(TIM2,300)
#define Right_Value_250 TIM_SetCompare1(TIM3,250)
#define Left_Value_250  TIM_SetCompare2(TIM2,250)
#define Right_Value_200 TIM_SetCompare1(TIM3,200)
#define Left_Value_200  TIM_SetCompare2(TIM2,200)
#define Right_Value_150 TIM_SetCompare1(TIM3,150)
#define Left_Value_150  TIM_SetCompare2(TIM2,150)
#define Right_Value_100 TIM_SetCompare1(TIM3,100)
#define Left_Value_100  TIM_SetCompare2(TIM2,100)
#define Right_Value_50  TIM_SetCompare1(TIM3,50)
#define Left_Value_50   TIM_SetCompare2(TIM2,50)



#endif



