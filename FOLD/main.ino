#include "main.h"

void main_setup()
{
	// Serial.begin(9600);
	switch_init();
	drive_init();
	echo_init();
}


void control_LB_2D_ez(float l_targ, float b_targ)
{
    struct p_control_result result_left;
    struct p_control_result result_back;

    struct p_control_args args_left;
    struct p_control_args args_back;

    drive_vector_t vec_left;
    drive_vector_t vec_back;
    drive_vector_t vec_result;

    vec_left.degrees = 180;
    vec_back.degrees = 270;

    control_clear_result(&result_left);
    control_clear_result(&result_back);

    args_left.pin_ultrasonic = PIN_ULTRASONIC_ECHO_LEFT;
    args_left.pk = 1.75f;
    args_left.max_speed = 255;
    args_left.abs_speed_dead_zone = 0;
    args_left.abs_speed_boost_zone = 0;
    args_left.echo_data_buf_count = 10;

    args_back.pin_ultrasonic = PIN_ULTRASONIC_ECHO_BACK;
    args_back.pk = 1.75f;
    args_back.max_speed = 255;
    args_back.abs_speed_dead_zone = 0;
    args_back.abs_speed_boost_zone = 0;
    args_back.echo_data_buf_count = 10;

    while(1)
    {
        args_left.mm_target = l_targ;
        args_left.mm_accuracy = 5;
        args_back.mm_target = b_targ;
        args_back.mm_accuracy = 5;

        delay(15);
        p_control_non_block(&result_left,&args_left);
        vec_left.speed = (result_left.result_speed);
        delay(15);
        p_control_non_block(&result_back,&args_back);
        vec_back.speed = (result_back.result_speed);
        vec_result = drive_combine_vecs(vec_left, vec_back, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            10.0f,
            60.0f
            ));

        go(vec_result);

        if(result_left.end_condition_count > 5
        	&& 
        	result_back.end_condition_count > 5)
        	break;
    }
}

void main_loop()
{
	go_stop();
	delay(1000);

	control_LB_2D_ez(200,200);
	go_stop();
	delay(1000);

	control_LB_2D_ez(400,400);
	go_stop();
	delay(1000);

	control_LB_2D_ez(600,600);
	go_stop();
	delay(1000);

	control_LB_2D_ez(700,30);
	go_stop();
	delay(1000);
}



