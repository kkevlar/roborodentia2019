#include "main.h"

void main_setup()
{
	// Serial.begin(9600);
	switch_init();
	drive_init();
	echo_init();
}

void main_loop()
{
	struct p_control_result result;
	struct p_control_args args_left;
	struct p_control_args args_back;
	drive_vector_t vec_left;
	drive_vector_t vec_back;
	drive_vector_t vec_result;

	vec_left.degrees = 180;
	vec_back.degrees = 270;

	args_left.pin_ultrasonic = PIN_ULTRASONIC_ECHO_LEFT;
    args_left.pk = 1.75f;
    args_left.max_speed = 255;
    args_left.abs_speed_dead_zone = 10;
    args_left.abs_speed_boost_zone = 60;
    args_left.max_end_condition_count = 5;

    args_back.pin_ultrasonic = PIN_ULTRASONIC_ECHO_BACK;
    args_back.pk = 1.75f;
    args_back.max_speed = 255;
    args_back.abs_speed_dead_zone = 10;
    args_back.abs_speed_boost_zone = 60;
    args_back.max_end_condition_count = 5;

	while(1)
	{
		args_left.mm_target = 400;
	    args_left.mm_cutoff = -595;
		args_back.mm_target = 400;
	    args_back.mm_cutoff = -295;

	    // result.end_condition_count = 5;
	    // while(result.end_condition_count > 0)
	    // {
	    delay(15);
		p_control_non_block(&result,&args_left);
		vec_left.speed = (result.result_speed);
	    delay(15);
		p_control_non_block(&result,&args_back);
		vec_back.speed = (result.result_speed);
		vec_result = drive_combine_vecs(vec_left, vec_back, 255);
		go(vec_result);
	// 	}

	// 	args_left.mm_target = 100;
	//     args_left.mm_cutoff = 105;
	// 	args_back.mm_target = 100;
	//     args_back.mm_cutoff = 105;

	//     result.end_condition_count = 5;
	//     while(result.end_condition_count > 0)
	//     {
	// 	p_control_non_block(&result,&args_left);
	// 	vec_left.speed = (result.result_speed);
	// 	p_control_non_block(&result,&args_back);
	// 	vec_back.speed = (result.result_speed);
	// 	vec_result = drive_combine_vecs(vec_left, vec_back, 255);
	// 	go(vec_result);
	// 	}
	}
}



