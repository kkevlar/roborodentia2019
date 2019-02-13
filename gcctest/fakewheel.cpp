#include "fakewheel.h"

int16_t wheel_speeds[4];

void wheel_init(void)
{
	printf("FakeWheel Module Initialized\n");

    wheel_speeds[0] = 0;
    wheel_speeds[1] = 0;
    wheel_speeds[2] = 0;
    wheel_speeds[3] = 0;
}

void print_wheels(void)
{
	printf("FL=%4d FR=%4d BL=%4d BR=%4d\n",
		wheel_speeds[0],
		wheel_speeds[1],
		wheel_speeds[2],
		wheel_speeds[3]
		);
}

//Assumed that if time = 0, then current speed is zero
void set_speed(uint8_t wheel, int16_t speed, int time)
{
	int wheel_index = 0;
   	if(wheel == WHEEL_FL)
   		wheel_index = 0;
   	if(wheel == WHEEL_FR)
   		wheel_index = 1;
   	if(wheel == WHEEL_BL)
   		wheel_index = 2;
   	if(wheel == WHEEL_BR)
   		wheel_index = 3;

	wheel_speeds[wheel_index] = speed;
  if(wheel==WHEEL_BR)
	print_wheels();   	
}



