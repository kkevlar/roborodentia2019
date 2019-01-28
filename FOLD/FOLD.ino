#include "FOLD.h"

void setup()
{
	switch_init();
	drive_init();
	echo_init();
	Serial.begin(9600);
}

void pcontrol(uint8_t pin_ultrasonic, int16_t mm_target, int16_t mm_cutoff, float pk, drive_vector_t vec, uint8_t pin_switch)
{
	double cm;
	double val;

	int degrees_orig = vec.degrees;
	do
	{	
		cm = echo_test_mm(pin_ultrasonic);
		Serial.println(cm);
		val = cm;
		val -= mm_target;
		val *= pk;
		if(val < 0)
		{
			val *= -1;
			vec.degrees = degrees_orig + 180;
		}
		else
		{
			vec.degrees = degrees_orig;
		}
		if(val > 255)
			val = 255;
		if (val < 20)
			val = 0;

		vec.speed = val;
		go(vec);
		delay(5);
	}
	while(cm > mm_cutoff);


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

void sprint_south(void)
{
	drive_vector_t vec;

	vec.degrees = 180;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_SOUTH,10,600,2,vec,PIN_SWITCH_SOUTH);
}

void safe_roomba_south(void)
{
	drive_vector_t vec;

	vec.degrees = 180;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_SOUTH,100,0,10,vec,-1);
}


// void sprint_south()
// {
// 	int degrees;
// 	double cm;
// 	drive_vector_t vec;
// 	uint8_t num_zeros = 0;

// 	vec.degrees = 180;
// 	vec.speed = 255;
// 	uint8_t num_zeros = 0;

// 	while(num_zeros < 10)
// 	{	
// 		cm = echo_test_mm(PIN_ULTRASONIC_ECHO_SOUTH);
// 		if(cm > 500)
// 			vec.speed = 255;
// 		else
// 		{
// 			num_zeros++;
// 			vec.speed = 0;
// 		}

// 		go(vec);
// 		delay(5);
// 	}
// }

void go_slow_into_wall_south(void)
{
	drive_vector_t vec;

	vec.degrees = 180;
	vec.speed = 90;
	while(!mass_switch_read())
	{
		go(vec);
		delay(10);
	}
	go_stop();
}

void position_west_close(void)
{
	drive_vector_t vec;

	vec.degrees = 180-70;
	vec.speed = 150;
	pcontrol(PIN_ULTRASONIC_ECHO_WEST,200,0,1,vec,-1);
}

void position_west_far(void)
{
	drive_vector_t vec;

	vec.degrees = 180+70;
	vec.speed = 150;
	pcontrol(PIN_ULTRASONIC_ECHO_WEST,800,0,1,vec,-1);
}

void roomba_activities()
{
	// sprint_south();
	delay(2000);
	safe_roomba_south();
	go_stop();
	delay(2000);
	go_north();
	delay(100);
	go_stop();
	delay(2000);
	go_slow_into_wall_south();
	while(1)
	{
	go_stop();
	delay(2000);
	}
	// while(1)
	// {
	// 	position_west_close();
	// 	position_west_far();
	// }
}


void loop()
{
	#ifdef TEST_ECHO
		echo_print_all();
		delay(250);
	#else
		roomba_activities();
	#endif
}

