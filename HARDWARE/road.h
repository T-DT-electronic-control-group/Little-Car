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

#define LED PCout(13)

void Road_Init(void);
void Road_Mode(void);


#endif


