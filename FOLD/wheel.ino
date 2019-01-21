
#include "wheel.h"

Adafruit_MotorShield AFMS_BOT(ADDR_BOT); // Rightmost jumper closed

uint8_t wheel_has_init = 0;
Adafruit_DCMotor *nw;
Adafruit_DCMotor *ne;
Adafruit_DCMotor *sw;
Adafruit_DCMotor *se;

void wheel_init(void)
{
    if(!wheel_has_init)
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
        wheel_has_init = 1;
    }
}

//Assumed that if time = 0, then current speed is zero
void set_speed(uint8_t wheel, int16_t speed, int time)
{
    Adafruit_DCMotor* motor;
    time = 0;

    if(wheel & WHEEL_NW)
        motor = nw;
    else if(wheel & WHEEL_NE)
        motor = ne;
    else if(wheel & WHEEL_SW)
        motor = sw;
    else
        motor = se;

    if (speed < 0)
    {
        speed = -speed;
        motor->run(BACKWARD);
    }
    else if (speed > 0)
    {
        motor->run(FORWARD);
    }
    if(speed > 255)
        speed = 255;
    
    if(time == 0 || speed == 0) //no ramp down
    {
        motor->setSpeed(speed);
        if (speed == 0)
            motor->run(RELEASE);
        return;
    }
    // for (int i=0; i<speed; i++) 
    // {
    //     motor->setSpeed(i);  
    //     delay(time/speed);
    // }
    if (speed == 0)
            motor->run(RELEASE);
}


