#ifndef __ROAD_H__
#define __ROAD_H__
#include "sys.h"
#include "motor.h"
#include "speed.h"
#include "remote.h"
#include "delay.h"

#define Left PBin(5)
#define Middle PBin(4)
#define Right PBin(3)

#define LED_ON GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_OFF GPIO_SetBits(GPIOC, GPIO_Pin_13)

#define BLACK 1
#define WRITE 0

//typedef enum MODE
//{
//	Mode1,
//	Mode2,
//	Mode3
//}
//ROAD_Mode;

void Road_Init(void);
void Road_Mode(void);


#endif


