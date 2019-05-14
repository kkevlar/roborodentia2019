
#include "aim.h"

uint16_t shoot_location_tally[AIM_LOCATION_COUNT];

void aim_init(void)
{
	uint32_t seed;

	pinMode(PIN_ANALOG_RANDOM, INPUT);
	delay(5);
	seed = analogRead(PIN_ANALOG_RANDOM);
	delay(5);
	seed *= analogRead(PIN_ANALOG_RANDOM);
	randomSeed(seed);

	for(seed = 0; seed < AIM_LOCATION_COUNT; seed++)
	{
		shoot_location_tally[seed] = 0;
	}
}

#define CLEAR_ALL_IS_MINS() for( \
		z = AIM_LOCATION_SELECTION_RANDOM_MIN;\
		z <= AIM_LOCATION_SELECTION_RANDOM_MAX;\
		z++)\
	{\
		is_min[z] = 0;\
	}\

#define TRUE_TO_ONE(b) (((b) ? (1) : (0)))

#ifndef GCCTEST
#define arduinoRandom(x) random(x)
#endif

aim_location_t aim_select_location()
{
	bool is_min[AIM_LOCATION_COUNT];
	uint16_t min_tally = 0;
	uint16_t count_cups = 0;
	int i;
	int z;

	CLEAR_ALL_IS_MINS();
	is_min[AIM_LOCATION_SELECTION_RANDOM_MIN] = 1;
	min_tally = shoot_location_tally[AIM_LOCATION_SELECTION_RANDOM_MIN];
	count_cups = 1;
	
	for(
		i = AIM_LOCATION_SELECTION_RANDOM_MIN+1;
		i <= AIM_LOCATION_SELECTION_RANDOM_MAX;
		i++)
	{


		if(min_tally == 
			shoot_location_tally[i])
		{
			count_cups++;
			is_min[i] = 1;
		}
		else if(min_tally > 
			shoot_location_tally[i])
		{
			CLEAR_ALL_IS_MINS();
			count_cups = 1;
			min_tally = shoot_location_tally[i];
			is_min[i] = 1;
		}
	}

	z = arduinoRandom(count_cups);
	for( i = AIM_LOCATION_SELECTION_RANDOM_MIN;
		i <= AIM_LOCATION_SELECTION_RANDOM_MAX;
		 i++)
	{
		z -= TRUE_TO_ONE(is_min[i]);
		if(z < 0)
			break;
	}

	shoot_location_tally[i]++;
	return i;
}


void aim_position_pre_roomba(direction_t dir_target, float mm_target)
{
    struct p_control_result result_wall;
    struct p_control_result result_target;

    struct p_control_args args_wall;
    struct p_control_args args_target;

    drive_vector_t vec_wall;
    drive_vector_t vec_target;
    drive_vector_t vec_result;

    vec_wall.degrees = direction_to_degrees(DIRECTION_ID_FRONT);
    vec_target.degrees = direction_to_degrees(dir_target);

    control_clear_result(&result_wall);
    control_clear_result(&result_target);

    args_wall.pin_ultrasonic = direction_to_echo_pin(DIRECTION_ID_FRONT);
    args_wall.pk = AIM_PRE_WALL_P_CONSTANT;
    args_wall.max_speed = 255;
    args_wall.abs_speed_dead_zone = 0;
    args_wall.abs_speed_boost_zone = 0;
    args_wall.echo_data_buf_count = 1;

    args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
    args_target.pk = AIM_PRE_TARGET_P_CONSTANT;
    args_target.max_speed = 255;
    args_target.abs_speed_dead_zone = 0;
    args_target.abs_speed_boost_zone = 0;
    args_target.echo_data_buf_count = 1;

    while(1)
    {
        args_wall.mm_target = AIM_PRE_DESIRED_WALL_DIST_MM;
        args_wall.mm_accuracy = AIM_PRE_MM_ACCURACY;
        args_target.mm_target = mm_target;
        args_target.mm_accuracy = AIM_PRE_MM_ACCURACY;

        delay(AIM_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
        p_control_non_block(&result_wall,&args_wall);
        vec_wall.speed = (result_wall.result_speed);
        delay(AIM_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS);
        p_control_non_block(&result_target,&args_target);
        vec_target.speed = (result_target.result_speed);
        vec_wall.speed = (result_wall.result_speed);
        vec_result = drive_combine_vecs(vec_wall, vec_target, 255);

        vec_result.speed = (int16_t) (control_treat_speed(
            (float) vec_result.speed,
            255.0f,
            10.0f,
            AIM_GENERAL_BOOST_ZONE
            ));

        go(vec_result);

        if(result_target.end_condition_count > 2 && 
            (result_wall.end_condition_count > 2 || result_wall.echo_avg < AIM_PRE_EARLY_BREAK_WALL_DIST))
            break;
    }
}

void aim_far_left()
{
	aim_position_pre_roomba(
		DIRECTION_ID_RIGHT,
		FIELD_AIM_PRE_CENTER_FROM_RIGHT);
}

void aim_center_left()
{
	aim_position_pre_roomba(
		DIRECTION_ID_RIGHT,
		FIELD_AIM_PRE_CENTER_FROM_RIGHT);
}

void aim_center()
{
	aim_position_pre_roomba(
		DIRECTION_ID_RIGHT,
		FIELD_AIM_PRE_CENTER_FROM_RIGHT);
}

void aim_center_right()
{
	aim_position_pre_roomba(
		DIRECTION_ID_RIGHT,
		FIELD_AIM_PRE_CENTER_FROM_RIGHT);
}

void aim_far_right()
{
	aim_position_pre_roomba(
		DIRECTION_ID_RIGHT,
		FIELD_AIM_PRE_CENTER_FROM_RIGHT);
}

void aim(aim_location_t loc)
{
	if(AIM_LOCATION_ID_FAR_LEFT == loc)
		aim_far_left();
	else if(AIM_LOCATION_ID_CENTER_LEFT == loc)
		aim_center_left();
	else if(AIM_LOCATION_ID_CENTER == loc)
		aim_center();
	else if(AIM_LOCATION_ID_CENTER_RIGHT == loc)
		aim_center_right();
	else if(AIM_LOCATION_ID_FAR_RIGHT == loc)
		aim_far_right();
}














