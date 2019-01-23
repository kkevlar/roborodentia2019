#include "echo.h"
 
void echo_init()
{
    pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
    pinMode(PIN_ULTRASONIC_ECHO_SOUTH, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_WEST, INPUT);
}

double echo_test_mm(uint8_t pin)
{
	long duration;
	double myout;

	digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
 
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH);

    myout = (duration);
    myout *= (0.171821f);
    return myout;
}

