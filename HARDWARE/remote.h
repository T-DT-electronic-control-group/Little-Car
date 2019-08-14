#ifndef __REMOTE_H__
#define __REMOTE_H__
#include "sys.h"

#define RDATA PBin(9)
#define REMOTE_ID 0  

extern u8 RmtCnt;	

void Remote_Init(void);

u8 Remote_Scan(void);

#define key_1 162
#define key_2 98
#define key_3 226
#define key_4 34
#define key_5 2
#define key_6 194
#define key_7 224
#define key_8 168
#define key_9 144
#define key_0 152
#define key_M 104
#define key_J 176
#define key_UP 24
#define key_RIGHT 90
#define key_LEFT 16
#define key_DOWN 74
#define key_OK 56

#endif







