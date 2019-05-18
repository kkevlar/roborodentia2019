
#include "wheel.h"

uint8_t wheel_has_init = 0;

void wheel_init(void)
{
    if(!wheel_has_init)
    {
        // Wire.begin();
        wheel_has_init = 1;
    }
}

uint8_t modes[4];
uint8_t speeds[4];

//Assumed that if time = 0, then current speed is zero
void set_speed(uint8_t wheel, int16_t speed, int time)
{
    uint8_t mode = 0;
    uint8_t packedSpeed = 0;
    time = 0;

    if (speed < 0)
    {
        speed = -speed;
        mode = SLAVE_MODE_REVERSE;
    }
    else if (speed > 0)
    {
        mode = SLAVE_MODE_FORWARD;
    }
    else if (speed == 0)
    {
        mode = SLAVE_MODE_RELEASE;
    }
    if(speed > WHEEL_GLOBAL_SPEED_CAP)
    {
        speed = WHEEL_GLOBAL_SPEED_CAP;
    }
    

    packedSpeed = speed;

    modes[wheel] = mode;
    speeds[wheel] = packedSpeed;
}

void wflush()
{
    Wire.beginTransmission(SLAVE_ADDRESS); // transmit to device #8

    for(int i = 0; i < 4; i++)
    {
        Wire.write(modes[i]);
        Wire.write(speeds[i]);
    }   
    Wire.endTransmission();
}


