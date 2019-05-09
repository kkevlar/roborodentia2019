
#include "shoot.h"

Adafruit_MotorShield AFMS_SHOOT(MOTOR_SHEILD_ADDRESS_SHOOT);
Servo flywheel_left;
Servo flywheel_right;
Adafruit_DCMotor *indexer;
Adafruit_DCMotor *conveyor_left;
Adafruit_DCMotor *conveyor_right;


void shoot_init(void)
{
    AFMS_SHOOT.begin();

    flywheel_left.attach(PIN_PWM_LEFT);
    flywheel_right.attach(PIN_PWM_RIGHT);

    indexer = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_INDEXER);
    conveyor_left = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_CONVEYOR_L);
    conveyor_right = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_CONVEYOR_R);

    flywheel_left.write(90);
    flywheel_right.write(90);
    indexer->run(RELEASE);
    conveyor_left->run(RELEASE);
    conveyor_right->run(RELEASE);
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


