
#include "collect.h"

void collect_init(void)
{
	/*Nobody's Home!!*/
	return;
}

void position_for_collection(direction_t dir_wall, direction_t dir_target, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_result result_target;

    struct p_control_args args_wall;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_wall);
    control_clear_result(&result_target);

    args_wall.pin_ultrasonic = direction_to_echo_pin(dir_wall);
    args_wall.pk = 2.0f;
    args_wall.max_speed = 255;
    args_wall.abs_speed_dead_zone = 0;
    args_wall.abs_speed_boost_zone = 0;
    args_wall.echo_data_buf_count = 1;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = 2.0f;
    args_target.max_speed = 255;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 1;

    while(1)
    {
        args_wall.mm_target = 60;
        args_wall.mm_accuracy = 10;
        args_target.mm_target = mm_target;
        args_target.mm_accuracy = 10;

        delay(10);
        p_control_non_block(&result_wall,&args_wall);
        vec_wall.speed = (result_wall.result_speed);
        delay(10);
        p_control_non_block(&result_target,&args_target);
        vec_target.speed = (result_target.result_speed);
        vec_wall.speed = (result_wall.result_speed);
        vec_result = drive_combine_vecs(vec_wall, vec_target, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            10.0f,
            60.0f
            ));

        go(vec_result);

        if(result_target.end_condition_count > 2 && 
            (result_wall.end_condition_count > 2 || result_wall.echo_avg < 150))
            break;
    }
}

void roomba(direction_t dir_wall)
{
    drive_vector_t vec_wall;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_wall.speed = 100;

    go(vec_wall);

    while(switch_test_up(dir_wall))
    {
        delay(5);
    }
}

void do_collection(direction_t dir_wall, direction_t dir_target, float mm_target)
{
    struct p_control_result result_target;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(dir_wall);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_target);

    vec_wall.speed = 70;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = 4.0f;
    args_target.max_speed = 150;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 1;
    args_target.mm_accuracy = 10;
    args_target.mm_target = mm_target;

    while(1)
    {
        delay(15);
        p_control_non_block(&result_target,&args_target);

        vec_target.speed = result_target.result_speed;

        vec_result = drive_combine_vecs(vec_target, vec_wall, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            10.0f,
            60.0f
            ));

        go(vec_result);

        if(result_target.end_condition_count > 2)
            break;
    }
}


void yeet_away_from_wall(direction_t dir_wall, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_args args_wall;

    drive_vector_t vec_wall;

    vec_wall.degrees = direction_to_degrees(dir_wall);

    control_clear_result(&result_wall);

    args_wall.pin_ultrasonic = direction_to_echo_pin(dir_wall);
    args_wall.pk = 1.0f;
    args_wall.max_speed = 255;
    args_wall.abs_speed_dead_zone = 0;
    args_wall.abs_speed_boost_zone = 80;
    args_wall.echo_data_buf_count = 1;
    args_wall.mm_accuracy = 25;
    args_wall.mm_target = mm_target;

    while(1)
    {
        delay(15);
        p_control_non_block(&result_wall,&args_wall);

        vec_wall.speed = result_wall.result_speed;

        go(vec_wall);

        if(result_wall.end_condition_count > 2)
            break;
    }
}

void collect_right()
{
    position_for_collection(DIRECTION_ID_RIGHT, DIRECTION_ID_BACK, 300);
    roomba(DIRECTION_ID_RIGHT);
    do_collection(DIRECTION_ID_RIGHT, DIRECTION_ID_BACK, 200);
}

void collect_back()
{
    position_for_collection(DIRECTION_ID_BACK, DIRECTION_ID_RIGHT, 500);
    roomba(DIRECTION_ID_BACK);
    do_collection(DIRECTION_ID_BACK, DIRECTION_ID_RIGHT, 600);
}

void collect_left()
{
    position_for_collection(DIRECTION_ID_LEFT, DIRECTION_ID_BACK, 200);
    roomba(DIRECTION_ID_LEFT);
    do_collection(DIRECTION_ID_LEFT, DIRECTION_ID_BACK, 300);
}

void collection_victory_lap()
{
    collect_right();
    collect_back();
    yeet_away_from_wall(DIRECTION_ID_BACK, 150);
    collect_left();
}


