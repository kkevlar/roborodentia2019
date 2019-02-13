
#include "control.h"

float signum(float f)
{
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 1;
}

void fill_p_control_result_default(struct p_control_result* result, struct p_control_args* args)
{
    result->result_speed = 0;
    result->end_condition_count = args->max_end_condition_count;
}

void fill_p_control_args_default(struct p_control_args* args)
{
    args->pin_ultrasonic = PIN_ULTRASONIC_ECHO_NORTH;
    args->mm_target = 100;
    args->mm_cutoff = 110;
    args->pk = 1;
    args->max_speed = 255;
    args->abs_speed_dead_zone = 20;
    args->abs_speed_boost_zone = 60;
    args->pin_switch = PIN_SWITCH_NORTH;
    args->max_end_condition_count = 5;
}

void p_control_non_block(struct p_control_result* result, struct p_control_args* args)
{
    uint16_t abs_max_speed;
    float cm;
    float val;

    abs_max_speed = ((uint16_t) abs(args->max_speed));
    
    cm = echo_test_mm(args->pin_ultrasonic);
    val = cm;
    val -= args->mm_target;
    val *= args->pk;

    if(abs(val) > abs_max_speed)
        val = abs_max_speed * signum(val);
    if (abs(val) < args->abs_speed_dead_zone)
        val = 0;
    else if (val < args->abs_speed_boost_zone)
        val = args->abs_speed_boost_zone;

    result->result_speed = (int16_t) val;

    if(args->mm_cutoff > 0)
    {
        if(cm < args->mm_cutoff)
            result->end_condition_count -= 1;
        else
            result->end_condition_count = result->end_condition_count+1 > args->max_end_condition_count ? args->max_end_condition_count : result->end_condition_count + 1;
    }
    if(args->mm_cutoff < 0 && cm > -args->mm_cutoff)
    {
        if(cm > -args->mm_cutoff)
            result->end_condition_count -= 1;
        else
            result->end_condition_count = result->end_condition_count+1 > args->max_end_condition_count ? args->max_end_condition_count : result->end_condition_count + 1;
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
 