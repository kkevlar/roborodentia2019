
#include <stdio.h>
#include "drive.h"
#include "cpTime.h"
#include <math.h>

int main()
{
	int degrees;
	drive_vector_t vec;

	printf("GccTest Module Initialized\n");
	drive_init();

	vec.speed = 255;

	for(degrees = 0; degrees < 360; degrees++)
	{
		vec.degrees = degrees;
		go(vec);
		cpSleep(300);
	}
}

