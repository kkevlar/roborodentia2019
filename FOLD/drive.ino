#include "drive.h"

void drive_init(void)
{
    wheel_init();
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

    angle = vec.degrees;
    angle *= 3.1415926f;
    angle /= 180;

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

    vec.degrees = 0;
    vec.speed = 255;

    go(vec);
}

void go_back()
{
    drive_vector_t vec;

    vec.degrees = 180;
    vec.speed = 255;

    go(vec);
}

void go_right()
{
    drive_vector_t vec;

    vec.degrees = 270;
    vec.speed = 255;

    go(vec);
}

void go_left()
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

