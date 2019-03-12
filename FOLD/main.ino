#include "main.h"

void main_setup()
{
	switch_init();
	drive_init();
	echo_init();
}

void main_loop()
{
	struct p_control_args args;
	struct p_control_result result;
	drive_vector_t vec;
	vec.degrees = 180;
	vec.speed = 255;

	args.pin_ultrasonic = PIN_ULTRASONIC_ECHO_LEFT;
    args.pk = 1.5f;
    args.max_speed = 255;
    args.abs_speed_dead_zone = 10;
    args.abs_speed_boost_zone = 60;
    // args.pin_switch = PIN_SWITCH_LEFT_BACK;
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



