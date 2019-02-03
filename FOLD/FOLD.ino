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
	float cm;
	float val;
	int count = 5;

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
		if(val > vec.speed)
			val = vec.speed;
		if (val < 10)
			val = 0;
		else if (val < 80)
			val = 80;

		vec.speed = val;
		go(vec);
		delay(1); // was 5
		if(mm_cutoff > 0)
			if(cm < mm_cutoff)
				count -= 1;
			else
				count = count+1 > 10 ? 10 : count + 1;
		if(mm_cutoff < 0 && cm > -mm_cutoff)
			if(cm > -mm_cutoff)
				count -= 1;
			else
				count = count+1 > 10 ? 10 : count + 1;
	}
	while(count > 0);


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
// 	float cm;
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

	vec.degrees = 90 + 5;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_WEST,150,170,2,vec,-1);
}

void position_west_far(void)
{
	drive_vector_t vec;

	vec.degrees = 90 - 15;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_WEST,700,-680,2,vec,-1);
}

void old_roomba_activities()
{
	// sprint_south();
	// delay(2000);
	// safe_roomba_south();
	// go_stop();
	// delay(2000);
	// go_north();
	// delay(100);
	go_stop();
	delay(2000);
	go_slow_into_wall_south();
	// while(1)
	// {
	// go_stop();
	// delay(2000);
	// }
	while(1)
	{
		position_west_close();
		go_stop();
		delay(1000);		
		position_west_far();
		go_stop();
		delay(1000);	

	}
}

void roomba_activities()
{
	float north;
	float south;
	float east;
	float west;
	float greatest;
	drive_vector_t vec;

	greatest = 0;


	vec.speed = 75;
	vec.degrees = 0;

	north = echo_test_mm(PIN_ULTRASONIC_ECHO_NORTH);
	south = echo_test_mm(PIN_ULTRASONIC_ECHO_SOUTH);
	east = echo_test_mm(PIN_ULTRASONIC_ECHO_EAST);
	west = echo_test_mm(PIN_ULTRASONIC_ECHO_WEST);

	if(north > greatest)
	{
		vec.degrees = 0;
		greatest = north;
	}
	if(south > greatest)
	{
		vec.degrees = 180;
		greatest = south;
	}
	if(east > greatest)
	{
		vec.degrees = 270;
		greatest = east;
	}
	if(west > greatest)
	{
		vec.degrees = 90;
		greatest = west;
	}

	go(vec);
}


void loop()
{
	#ifdef TEST_ECHO
		echo_print_all();
		delay(50);
	#else
		old_roomba_activities();
		delay(5);
		// go_stop();
		// delay(150);
		// go_north();
		// delay(150);
		// go_stop();
		// delay(150);
		// go_south();
		// delay(150);
		// go_stop();
		// delay(150);
		// go_east();
		// delay(150);
		// go_stop();
		// delay(150);
		// go_west();
		// delay(150);
		// go_stop();
		// delay(150);
	#endif
}

