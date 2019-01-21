
#include "drive.h"

Adafruit_MotorShield AFMS_BOT(ADDR_BOT); // Rightmost jumper closed

Adafruit_DCMotor *nw;
Adafruit_DCMotor *ne;
Adafruit_DCMotor *sw;
Adafruit_DCMotor *se;

void drive_init(void)
{
    AFMS_BOT.begin();  // create with the default frequency 1.6KHz
   
    nw = AFMS_BOT.getMotor(BOT_PORT_NW);
    ne = AFMS_BOT.getMotor(BOT_PORT_NE);
    sw = AFMS_BOT.getMotor(BOT_PORT_SW);
    se = AFMS_BOT.getMotor(BOT_PORT_SE);
    
    nw->run(RELEASE);
    ne->run(RELEASE);
    sw->run(RELEASE);
    se->run(RELEASE);
}

//Assumed that if time = 0, then current speed is zero
void set_speed(Adafruit_DCMotor* motor, int16_t speed, int time)
{
    if (speed < 0)
    {
        speed = -speed;
        motor->run(BACKWARD);
    }
    else if (speed > 0)
    {
        motor->run(FORWARD);
    }
    if(time == 0 || speed == 0) //no ramp down
    {
        motor->setSpeed(speed);
        if (speed == 0)
            motor->run(RELEASE);
        return;
    }
    for (int i=0; i<speed; i++) 
    {
        motor->setSpeed(i);  
        delay(time/speed);
    }
    if (speed == 0)
            motor->run(RELEASE);
}

void go(drive_vector_t vec)
{
    int16_t speed_nw;
    int16_t speed_ne;
    int16_t speed_sw;
    int16_t speed_se;
    float angle;
    float speed_default;

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

    set_speed(nw, OFFSET_NW * speed_nw, 0);
    set_speed(ne, OFFSET_NE * speed_ne, 0);
    set_speed(sw, OFFSET_SW * speed_sw, 0);
    set_speed(se, OFFSET_SE * speed_se, 0);
}

void go_north()
{
    drive_vector_t vec;

    vec.degrees = 90;
    vec.speed = 255;

    go(vec);
}

void go_south()
{
    drive_vector_t vec;

    vec.degrees = 90*3;
    vec.speed = 255;

    go(vec);
}

void go_east()
{
    drive_vector_t vec;

    vec.degrees = 0;
    vec.speed = 255;

    go(vec);
}

void go_west()
{
    drive_vector_t vec;

    vec.degrees = 180;
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

