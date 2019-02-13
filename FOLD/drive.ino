#include "drive.h"

void drive_init(void)
{
    wheel_init();
}

void go(drive_vector_t vec)
{
    int16_t speed_nw;
    int16_t speed_ne;
    int16_t speed_sw;
    int16_t speed_se;
    int16_t speed_max;
    float angle;
    float speed_default;
    float scale;

    angle = vec.degrees;
    angle *= 3.1415926f;
    angle /= 180;

    speed_default = vec.speed;

    speed_nw = speed_default * sin(angle);
    speed_ne = speed_default * sin(angle);
    speed_sw = speed_default * -sin(angle);
    speed_se = speed_default * -sin(angle);

    speed_nw += speed_default * cos(angle);
    speed_ne += speed_default * -cos(angle);
    speed_sw += speed_default * cos(angle);
    speed_se += speed_default * -cos(angle);

    speed_max = speed_nw;
    if(speed_ne > speed_max)
        speed_max = speed_ne;
    if(speed_sw > speed_max)
        speed_max = speed_sw;
    if(speed_se > speed_max)
        speed_max = speed_se;

    scale = speed_default/speed_max;

    speed_nw *= scale;
    speed_ne *= scale;
    speed_sw *= scale;
    speed_se *= scale;

    set_speed(WHEEL_NW, OFFSET_NW * speed_nw, 0);
    set_speed(WHEEL_NE, OFFSET_NE * speed_ne, 0);
    set_speed(WHEEL_SW, OFFSET_SW * speed_sw, 0);
    set_speed(WHEEL_SE, OFFSET_SE * speed_se, 0);
}

void go_north()
{
    drive_vector_t vec;

    vec.degrees = 0;
    vec.speed = 255;

    go(vec);
}

void go_south()
{
    drive_vector_t vec;

    vec.degrees = 180;
    vec.speed = 255;

    go(vec);
}

void go_east()
{
    drive_vector_t vec;

    vec.degrees = 270;
    vec.speed = 255;

    go(vec);
}

void go_west()
{
    drive_vector_t vec;

    vec.degrees = 90;
    vec.speed = 255;

    go(vec);
}

void go_stop()
{
    drive_vector_t vec;

    vec.degrees = 0;
    vec.speed = 0;

    go(vec);
}

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

