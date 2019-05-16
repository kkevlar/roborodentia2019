
#include "shoot.h"

Adafruit_MotorShield AFMS_SHOOT(MOTOR_SHEILD_ADDRESS_SHOOT);
Servo flywheel_left;
Servo flywheel_right;
Adafruit_DCMotor *indexer;
Adafruit_DCMotor *conveyor_left;
Adafruit_DCMotor *conveyor_right;

#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds


void shoot_init(void)
{
    AFMS_SHOOT.begin();

    indexer = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_INDEXER);
    conveyor_left = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_CONVEYOR_L);
    conveyor_right = AFMS_SHOOT.getMotor(MOTOR_SHEILD_PORT_CONVEYOR_R);

    flywheel_left.write(SHOOT_STOPPED_FLYWHEEL_LEFT);
    // flywheel_right.write(SHOOT_STOPPED_FLYWHEEL_RIGHT);
    indexer->run(RELEASE);
    conveyor_left->run(RELEASE);
    conveyor_right->run(RELEASE);

    // delay(2000);


    /*lcd_print_bot("arming");
    myESC.arm(); 

    delay();

    myESC.speed(1500);*/
    
    delay(1000);

    flywheel_left.attach(PIN_PWM_LEFT,1000,2000);
    // flywheel_right.attach(PIN_PWM_RIGHT);


    flywheel_left.write(500);
    // flywheel_right.write(180);

    delay(1000);

    lcd_print_bot("0...");


    flywheel_left.write(1000);
    // flywheel_right.write(0);

    delay(1000);


    lcd_print_bot("90...");

    flywheel_left.write(2000);

    delay(500);
    // flywheel_right.write(90);*/

}

void shoot_set_speed(Adafruit_DCMotor* motor, int16_t speed)
{
    if(motor == conveyor_left)
        speed *= MOTOR_MULTIPLIER_CONVEYOR_L;
    if(motor == conveyor_right)
        speed *= MOTOR_MULTIPLIER_CONVEYOR_R;
    if(motor == indexer)
        speed *= MOTOR_MULTIPLIER_INDEXER;

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

void shoot_flywheel_left_start(void)
{
    flywheel_left.write(SHOOT_SPEED_FLYWHEEL_LEFT);
}

void shoot_flywheel_right_start(void)
{
    // flywheel_right.write(SHOOT_SPEED_FLYWHEEL_RIGHT);
}

void shoot_flywheel_left_stop(void)
{
    flywheel_left.write(SHOOT_STOPPED_FLYWHEEL_LEFT);
}

void shoot_flywheel_right_stop(void)
{
    // flywheel_right.write(SHOOT_STOPPED_FLYWHEEL_RIGHT);
}

void shoot_flywheel_both_start(void)
{
    shoot_flywheel_left_start();
    shoot_flywheel_right_start();
}

void shoot_flywheel_both_stop(void)
{
    shoot_flywheel_left_stop();
    shoot_flywheel_right_stop();
}


void shoot_conveyor_left_start(void)
{
    shoot_set_speed(conveyor_left, SHOOT_SPEED_CONVEYOR_LEFT);
}

void shoot_conveyor_right_start(void)
{
    shoot_set_speed(conveyor_right, SHOOT_SPEED_CONVEYOR_RIGHT);
}

void shoot_conveyor_both_start(void)
{
    shoot_conveyor_left_start();
    shoot_conveyor_right_start();
}

void shoot_conveyor_left_stop(void)
{
    shoot_set_speed(conveyor_left, 0);
}

void shoot_conveyor_right_stop(void)
{
    shoot_set_speed(conveyor_right, 0);
}

void shoot_conveyor_both_stop(void)
{
    shoot_conveyor_left_stop();
    shoot_conveyor_right_stop();
}

void shoot_indexer_start(void)
{
    shoot_set_speed(indexer, SHOOT_SPEED_INDEXER_FORWARD);
}

void shoot_indexer_stop(void)
{
    shoot_set_speed(indexer, 0);
}

void shoot_indexer_spam(void)
{
    long l;

    l = millis();
    l /= 1000;

    if(l % 2 == 0)
        shoot_set_speed(indexer, SHOOT_SPEED_INDEXER_FORWARD);
    else
        shoot_set_speed(indexer, SHOOT_SPEED_INDEXER_BACKWARD);
}





