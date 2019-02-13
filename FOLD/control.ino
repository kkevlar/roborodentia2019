
#include "control.h"

float signum(float f)
{
    if (f > 0) return 1;
    if (f < 0) return -1;
    return 1;
}

void p_control_non_block(
    int16_t* result_speed,
    uint16_t* end_condition_count,
    uint8_t pin_ultrasonic,
    int16_t mm_target,
    int16_t mm_cutoff,
    float pk,
    int16_t max_speed,
    uint8_t pin_switch,
    uint16_t max_end_condition_count)
{
    float cm;
    float val;

    max_speed = abs(max_speed);
    
    cm = echo_test_mm(pin_ultrasonic);
    val = cm;
    val -= mm_target;
    val *= pk;

    if(abs(val) > max_speed)
        val = max_speed * signum(val);
    if (abs(val) < 10)
        val = 0;
    else if (val < 80)
        val = 80;

    *result_speed = (int16_t) val;

    if(mm_cutoff > 0)
    {
        if(cm < mm_cutoff)
            *end_condition_count -= 1;
        else
            *end_condition_count = *end_condition_count+1 > max_end_condition_count ? max_end_condition_count : *end_condition_count + 1;
    }
    if(mm_cutoff < 0 && cm > -mm_cutoff)
    {
        if(cm > -mm_cutoff)
            *end_condition_count -= 1;
        else
            *end_condition_count = *end_condition_count+1 > max_end_condition_count ? max_end_condition_count : *end_condition_count + 1;
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
 