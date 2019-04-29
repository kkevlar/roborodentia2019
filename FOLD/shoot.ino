
#include "shoot.h"

Adafruit_MotorShield AFMS_SHOOT(MOTOR_SHEILD_ADDRESS_SHOOT);

void shoot_init(void)
{
    
}

void shoot_set_speed(Adafruit_DCMotor* motor, int16_t speed)
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
    if(speed > 255)
        speed = 255;
 
    motor->setSpeed(speed);
    if (speed == 0)
        motor->run(RELEASE);
    return;
}


