#include "FOLD.h"

void setup()
{
	drive_init();
	echo_init();
}

void loop()
{
	int degrees;
	double cm;
	drive_vector_t vec;

	vec.degrees = 180;

	while(1)
	{	
		cm = echo_test_mm();
		cm -= 600;
		cm *= 10;
		if(cm < 0)
		{
			cm *= -1;
			vec.degrees = 0;
		}
		else
		{
			vec.degrees = 180;
		}
		if(cm > 255)
			cm = 255;
		if (cm < 20)
			cm = 0;

		vec.speed = cm;
		go(vec);
		delay(5);
	}

	//300 --> 30cm
	//800 --> 87cm
	//500 --> 56cm
	//200 --> 20cm
	//150 --> 15cm
	//450 --> 50cm
	//350 --> 40cm
	//100 --> 11cm
	//75 --> 7.5cm
	//250 --> 27cm
	//600 --> 64cm
}

