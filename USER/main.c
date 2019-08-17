#include "sys.h"
#include "init.h"

int main(void)
{
	u8 value;
	uint16_t speed;
	All_Init();
	
	speed = Speed1;
	
	while(1)
	{
		value = Remote_Scan();
		
		speed=Select_Speed(value);
		
		switch(value)
		{
			case key_UP:
				Forward_car(speed);
			  break;
			case key_DOWN:
				Backward_car(speed);
			  break;
			case key_RIGHT:
				Right_car(speed);
			  break;
			case key_LEFT:
				Left_car(speed);
			  break;
			case key_0:
				Road_Mode();
			  LED=1;
			  break;
			case key_OK:
				Pause();
			  break;
		}
	}
}

