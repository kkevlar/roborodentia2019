
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS_BOT(0x61);

Adafruit_DCMotor *motor;

void setup() 
{
	pinMode(2,INPUT_PULLUP);
	pinMode(13,OUTPUT);
	 AFMS_BOT.begin();
    motor = AFMS_BOT.getMotor(1);
    motor->run(RELEASE);
}

void set_speed(int16_t speed, int time)
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
    
    if(time == 0 || speed == 0) //no ramp down
    {
        motor->setSpeed(speed);
        if (speed == 0)
            motor->run(RELEASE);
        return;
    }
    // for (int i=0; i<speed; i++) 
    // {
    //     motor->setS(0x6peed(i);  
    //     delay(time/speed);
    // }
    if (speed == 0)
            motor->run(RELEASE);
}

void loop() 
{
	if(digitalRead(2))
		set_speed(0,0);
	else
		set_speed(255,0);
}
