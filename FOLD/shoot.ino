
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

    flywheel_left.write(SHOOT_STOPPED_FLYWHEEL_LEFT);
    flywheel_right.write(SHOOT_STOPPED_FLYWHEEL_RIGHT);
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

void shoot_flywheel_left_start()
{
    flywheel_left.write(SHOOT_SPEED_FLYWHEEL_LEFT);
}

void shoot_flywheel_right_start()
{
    flywheel_right.write(SHOOT_SPEED_FLYWHEEL_RIGHT);
}

void shoot_flywheel_left_stop()
{
    flywheel_left.write(SHOOT_STOPPED_FLYWHEEL_LEFT);
}

void shoot_flywheel_right_stop()
{
    flywheel_right.write(SHOOT_STOPPED_FLYWHEEL_RIGHT);
}

void shoot_flywheel_both_start()
{
    shoot_flywheel_left_start();
    shoot_flywheel_right_start();
}

void shoot_flywheel_both_stop()
{
    shoot_flywheel_left_stop();
    shoot_flywheel_right_stop();
}


void shoot_conveyor_left_start()
{
    shoot_set_speed(conveyor_left, SHOOT_SPEED_CONVEYOR_LEFT);
}

void shoot_conveyor_right_start()
{
    shoot_set_speed(conveyor_right, SHOOT_SPEED_CONVEYOR_RIGHT);
}

void shoot_conveyor_both_start()
{
    shoot_conveyor_left_start();
    shoot_conveyor_right_start();
}

void shoot_conveyor_left_stop()
{
    shoot_set_speed(conveyor_left, 0);
}

void shoot_conveyor_right_stop()
{
    shoot_set_speed(conveyor_right, 0);
}

void shoot_conveyor_both_stop()
{
    shoot_conveyor_left_stop();
    shoot_conveyor_right_stop();
}

void shoot_indexer_start()
{
    shoot_set_speed(indexer, SHOOT_SPEED_INDEXER_FORWARD);
}

void shoot_indexer_stop()
{
    shoot_set_speed(indexer, 0);
}

void shoot_indexer_unjam()
{
    shoot_set_speed(indexer, SHOOT_SPEED_INDEXER_BACKWARD);
}





