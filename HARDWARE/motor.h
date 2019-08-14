#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "sys.h"

//L298n ENA,ENBÊ¹ÄÜ  PB.6  PB.7
#define L298n_ENA PBout(6)
#define L298n_ENB PBout(7)

//PWM¡°²Î¿¼¶Ë¡±
#define R PAout(2)
#define L PAout(3)

//#define LED PCout(13)

#define Speed0 0
#define Speed1 450
#define Speed2 500
#define Speed3 600

enum Direction
{
	Forward=0,
	Backward=1
};

extern enum Direction direction;

void L298n_Init(void);

void Forward_car(uint16_t Speed);
void Backward_car(uint16_t Speed);
void Right_car(uint16_t speed);
void Left_car(uint16_t speed);
void Pause(void);

uint16_t Select_Speed(u8 value);

#endif


