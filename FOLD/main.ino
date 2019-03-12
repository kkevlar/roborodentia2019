#include "main.h"

void main_setup()
{
	switch_init();
	drive_init();
	echo_init();
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

void sprint_back(void)
{
	drive_vector_t vec;

	vec.degrees = 180;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_BACK,150,250,5,vec,PIN_SWITCH_BACK);
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

void go_slow_into_wall_back(void)
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

void position_left_close(void)
{
	drive_vector_t vec;

	vec.degrees = 90 + 5;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_LEFT,150,170,2,vec,-1);
}

void position_left_far(void)
{
	drive_vector_t vec;

	vec.degrees = 90 - 15;
	vec.speed = 255;
	pcontrol(PIN_ULTRASONIC_ECHO_LEFT,700,-680,2,vec,-1);
}

void old_roomba_activities()
{
	sprint_back();
	// go_stop();
	// delay(500);
	// safe_roomba_south();
	// go_stop();
	// delay(2000);
	// go_north();
	// delay(100);
	// go_stop();
	// delay(2000);
	go_slow_into_wall_back();
	// while(1)
	// {
	// go_stop();
	// delay(2000);
	// }
	while(1)
	{
		position_left_close();
		go_stop();
		delay(100);		
		position_left_far();
		go_stop();
		delay(100);	

	}
}

void main_loop()
{
	struct p_control_args args;
	struct p_control_result result;
	drive_vector_t vec;
	vec.degrees = 180;
	vec.speed = 255;
	vec.maxspeed = 255;

	args.pin_ultrasonic = PIN_ULTRASONIC_ECHO_LEFT;
    args.pk = 1.5f;
    args.max_speed = 255;
    args.abs_speed_dead_zone = 10;
    args.abs_speed_boost_zone = 60;
    args.pin_switch = PIN_SWITCH_LEFT_BACK;
    args.max_end_condition_count = 5;


	while(1)
	{
		args.mm_target = 600;
	    args.mm_cutoff = -595;
	    result.end_condition_count = 5;

	    while(result.end_condition_count > 0)
	    {
		p_control_non_block(&result,&args);
		vec.speed = (result.result_speed);
		go(vec);
		}
		args.mm_target = 100;
	    args.mm_cutoff = 105;
	    result.end_condition_count = 5;
	    while(result.end_condition_count > 0)
	    {
		p_control_non_block(&result,&args);
		vec.speed = (result.result_speed);
		go(vec);
		}
	}
}



