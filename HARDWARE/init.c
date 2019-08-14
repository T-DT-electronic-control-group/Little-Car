#include "init.h"

void All_Init(void)
{
	L298n_Init();
	TIM2_PWM_Init(899,0);
	TIM3_PWM_Init(899,0);
	Remote_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();
	uart_init(115200);
}


