#include "FOLD.h"

void setup()
{
	drive_init();
	echo_init();
}

void loop()
{
	int degrees;
	drive_vector_t vec;

	vec.speed = 255;

	for(degrees = 0; degrees < 360; degrees++)
	{
		vec.degrees = degrees;
		go(vec);
		delay(30);
	}

	echo_loop();
}

