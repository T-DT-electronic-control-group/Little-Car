#ifndef __SPEED_H__
#define __SPEED_H__

#include "sys.h"

//使用 TIM3_CH1  PA.6
void TIM3_PWM_Init(u16 arr,u16 psc);

//使用 TIM2_CH2  PA.1
void TIM2_PWM_Init(u16 arr,u16 psc);

#endif

