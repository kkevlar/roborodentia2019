#include "main.h"

void main_setup()
{
	// Serial.begin(9600);
	switch_init();
	drive_init();
	echo_init();
}

/*
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
    //  }

    //  args_left.mm_target = 100;
    //     args_left.mm_cutoff = 105;
    //  args_back.mm_target = 100;
    //     args_back.mm_cutoff = 105;

    //     result.end_condition_count = 5;
    //     while(result.end_condition_count > 0)
    //     {
    //  p_control_non_block(&result,&args_left);
    //  vec_left.speed = (result.result_speed);
    //  p_control_non_block(&result,&args_back);
    //  vec_back.speed = (result.result_speed);
    //  vec_result = drive_combine_vecs(vec_left, vec_back, 255);
    //  go(vec_result);
    //  }
    }
}
*/


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

void echo_test_until(
    uint8_t pin,
    float dist,
    uint8_t getting_closer,
    uint8_t count)
{
    float mm;

    while(count > 0)
    {
        mm = echo_test_mm(pin);
        if(
            (mm < dist && getting_closer) ||
            (mm > dist && !getting_closer) )
        {
            count--;
        }

        delay(15);
    }
}




void position_for_collection(float targ)
{
    struct p_control_result result;
    struct p_control_args args;

    drive_vector_t vec_p;
    drive_vector_t vec_left;
    drive_vector_t vec_result;

    vec_left.degrees = 180;
    vec_p.degrees = 270;

    vec_left.speed = 60;

    control_clear_result(&result);

    args.pin_ultrasonic = PIN_ULTRASONIC_ECHO_BACK;
    args.pk = 1.75f;
    args.max_speed = 255;
    args.abs_speed_dead_zone = 0;
    args.abs_speed_boost_zone = 0;
    args.echo_data_buf_count = 3;
    args.mm_target = targ;
    args.mm_accuracy = 3;

    while(1)
    {

        delay(15);
        p_control_non_block(&result,&args);
        vec_p.speed = result.result_speed;
        vec_result = drive_combine_vecs(vec_left, vec_p, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            10.0f,
            60.0f
            ));

        go(vec_result);

        if(result.end_condition_count > 5)
            break;
    }
}

void bigtest()
{
    go_stop();
    delay(1000);

    go_left();
    delay(100);
    echo_test_until(PIN_ULTRASONIC_ECHO_LEFT, 400, 1, 5);

    go_stop();
    delay(2000);
    position_for_collection(700);

    go_stop();
    delay(100000);
}


