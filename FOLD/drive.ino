#include "drive.h"

void drive_init(void)
{
    wheel_init();
}

int16_t direction_to_degrees(direction_t dir)
{
    if(dir == DIRECTION_ID_FRONT)
        return DEGREES_FRONT;
    else if(dir == DIRECTION_ID_BACK)
        return DEGREES_BACK;
    else if(dir == DIRECTION_ID_LEFT)
        return DEGREES_LEFT;
    else if(dir == DIRECTION_ID_RIGHT)
        return DEGREES_RIGHT;

    return 0;
}

int16_t drive_easy_atan(int16_t fb, int16_t rl)
{
    uint16_t deg;
    float rad;

    rad = atan2((float) fb, (float) rl);
    rad *= 180.0f;
    rad /= 3.1415f;

    deg = (uint16_t) rad;
    return deg;
}

void drive_fix_vector(drive_vector_t* vec)
{
    if(vec->speed < 0)
    {
        vec->speed = -vec->speed;
        vec->degrees += 180;
    }
}

float drive_degrees_to_rad(float degrees)
{
    float rad;
    rad = degrees;
    rad *= 3.1415926f;
    rad /= 180;
    return rad;
}

int16_t drive_rad_to_degrees(float rad)
{
    float degrees;
    degrees = rad;
    degrees /= 3.1415926f;
    degrees *= 180;
    return (int16_t) degrees;
}

void drive_calc_xy(drive_vector_t vec, float* fb, float* lr)
{
    float angle;

    drive_fix_vector(&vec);
    angle = drive_degrees_to_rad(vec.degrees);
    *fb = vec.speed * cos(angle);
    *lr = vec.speed * sin(angle);
}

drive_vector_t drive_combine_vecs(drive_vector_t a, drive_vector_t b, int speed_max)
{
    drive_vector_t res;
    float a_lr;
    float a_fb;
    float b_lr;
    float b_fb;
    float rad;

    drive_calc_xy(a, &a_fb, &a_lr);
    drive_calc_xy(b, &b_fb, &b_lr);

    // char buf[20];
    // snprintf(buf,20,"%d %d %d %d %d %d",
    //     a.speed,
    //     b.speed,
    //     (int) a_fb,
    //     (int) a_lr,
    //     (int) b_fb,
    //     (int) b_lr
    //     );
    // Serial.println(buf);

    a_lr += b_lr;
    a_fb += b_fb;
    rad = atan2(a_lr,a_fb);

    res.degrees = drive_rad_to_degrees(rad);
    res.speed = abs(a.speed) > abs(b.speed) ? abs(a.speed) : abs(b.speed);/*
    res.speed += a.speed * a.speed;
    res.speed += b.speed * b.speed;
    res.speed = sqrt(res.speed);*/
    return res;
}

void go(drive_vector_t vec)
{
    int16_t speed_fl;
    int16_t speed_fr;
    int16_t speed_bl;
    int16_t speed_br;
    int16_t speed_max;
    float angle;
    float speed_default;
    float scale;

    drive_fix_vector(&vec);

    angle = drive_degrees_to_rad(vec.degrees);
    speed_default = vec.speed;

    speed_fl = speed_default * cos(angle);
    speed_fr = speed_default * cos(angle);
    speed_bl = speed_default * -cos(angle);
    speed_br = speed_default * -cos(angle);

    speed_fl += speed_default * sin(angle);
    speed_fr += speed_default * -sin(angle);
    speed_bl += speed_default * sin(angle);
    speed_br += speed_default * -sin(angle);

    speed_max = speed_fl;
    if(speed_fr > speed_max)
        speed_max = speed_fr;
    if(speed_bl > speed_max)
        speed_max = speed_bl;
    if(speed_br > speed_max)
        speed_max = speed_br;

    scale = speed_default/speed_max;

    speed_fl *= scale;
    speed_fr *= scale;
    speed_bl *= scale;
    speed_br *= scale;

    set_speed(WHEEL_FL, OFFSET_FL * speed_fl, 0);
    set_speed(WHEEL_FR, OFFSET_FR * speed_fr, 0);
    set_speed(WHEEL_BL, OFFSET_BL * speed_bl, 0);
    set_speed(WHEEL_BR, OFFSET_BR * speed_br, 0);
}

void go_front()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_FRONT);
    vec.speed = 255;

    go(vec);
}

void go_back()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_BACK);
    vec.speed = 255;

    go(vec);
}

void go_right()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_RIGHT);
    vec.speed = 255;

    go(vec);
}

void go_left()
{
    drive_vector_t vec;

    vec.degrees = direction_to_degrees(DIRECTION_ID_LEFT);
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

