
#include <Adafruit_MotorShield.h>
#include <Servo.h>

Adafruit_MotorShield AFMS_BOT(0x61); // Rightmost jumper closed

Servo myservo;

void setup(void)
{        
	AFMS_BOT.begin();
       
    myservo.attach(SERVO_1,1000,2000);

	delay(5000);

}

void loop()
{

	myservo.write(0);

	delay (500);

	myservo.write(180);

	delay(500);
}
