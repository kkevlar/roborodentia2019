#include "echo.h"
 
void echo_init()
{
    pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
    pinMode(PIN_ULTRASONIC_ECHO, INPUT);

    // Serial.begin(9600);
    // Serial.println("Init");
}

double echo_test_mm()
{
	long duration;
	double myout;

	digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
 
    pinMode(PIN_ULTRASONIC_ECHO, INPUT);
    duration = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);

    myout = (duration);
    myout *= (0.171821f);
    return myout;
}
 
// void echo_loop() 
// {
//     long duration, cm, inches;

//     digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
//     delayMicroseconds(5);
//     digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
 
//     pinMode(PIN_ULTRASONIC_ECHO, INPUT);
//     duration = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);
 
//     cm = (duration/2) / 29.1;
//     inches = (duration/2) / 74;
  
//     Serial.print(inches);
//     Serial.print("in, ");
//     Serial.print(cm);
//     Serial.print("cm");
//     Serial.println();

//     delay(250);
// }
